/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_mailbox_ifc.c
  版 本 号   : 初稿
  生成日期   : 2013年4月11日
  最近修改   :
  功能描述   : mailbox&跨核邮箱驱动软件，核间调用主体代码。
  函数列表   :

  修改历史   :
  1.日    期   : 2013年4月11日
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "drv_mailbox.h"
#include "drv_mailbox_cfg.h"
#include "drv_mailbox_debug.h"
#include "drv_mailbox_gut.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    可维可测信息中包含的C文件编号宏定义
*****************************************************************************/
#undef  _MAILBOX_FILE_
#define _MAILBOX_FILE_   "msg"
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
extern int BSP_CPU_StateGet(int CpuID);
/*****************************************************************************
 函 数 名  : mailbox_msg_receiver
 功能描述  : 核间邮件数据接收回调函数的注册
 输入参数  : void *mb_buf     -- 邮箱物理通道句柄。
             void *handle     -- 用户句柄.
             void *data       -- 用户数据.
 输出参数  : 无
 返 回 值  : MAILBOX_OK, 异常返回值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月29日
    修改内容   : 新生成函数

*****************************************************************************/

void mailbox_msg_receiver(void *mb_buf, void *handle, void *data)
{
    struct mb_queue * queue;  /*邮箱buffer临时句柄，用于传给用户回调*/
    struct mb_buff  * mbuf = ( struct mb_buff  *)mb_buf;
    mb_msg_cb  func = (mb_msg_cb)handle;
    unsigned long ret_val = 0; /* Fix warning "statement with no effect" (by zwx206529)*/

    queue = &mbuf->usr_queue;
    if (func) {
        func(data, (void *)queue, queue->size);
    } else {
        ret_val = mailbox_logerro_p1(MAILBOX_ERR_GUT_READ_CALLBACK_NOT_FIND, mbuf->mailcode);
    }
}

MAILBOX_EXTERN unsigned long mailbox_reg_msg_cb(
                unsigned long             mailcode,
                mb_msg_cb                 func,
                void                     *data)
{
    return (unsigned long)mailbox_register_cb(mailcode, mailbox_msg_receiver, func, data);
}

/*****************************************************************************
 函 数 名  : mailbox_try_send_msg
 功能描述  : 进行一次邮件发送动作
 输入参数  :
             unsigned long      mailcode        -- 邮箱逻辑通道号
             unsigned char      *pdata           -- 指向邮件数据的指针。
             unsigned long      length/byte     -- 数据或者消息总长度 字节为单位。
 输出参数  : 无
 返 回 值  : unsigned long
             成功OK, 异常返回值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月28日
    修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_EXTERN unsigned long mailbox_try_send_msg(
                unsigned long            mailcode,
                void                    *pdata,
                unsigned long            length)
{
    struct mb_buff      *mb_buf = MAILBOX_NULL;
    struct mb_queue     *queue  = MAILBOX_NULL;
    unsigned long        ret_val    = MAILBOX_OK;
    
   if ((0 == pdata) || (0 == length)) {
        ret_val = (unsigned long)mailbox_logerro_p1(MAILBOX_ERRO, mailcode);
        goto exit_out;

   }
    /*获取邮箱buffer*/ 
    ret_val = mailbox_request_buff(mailcode, (void *)&mb_buf);
    if (MAILBOX_OK != ret_val) {
        goto exit_out;
    }

    /*填充用户数据*/
    queue = &mb_buf->usr_queue;
    if ( length != mailbox_write_buff( queue, pdata, length)) {
         ret_val = (unsigned long)mailbox_logerro_p1(MAILBOX_FULL, mailcode);
         goto exit_out;
    }

    /*封信*/
    ret_val = mailbox_sealup_buff( mb_buf,  length);
    if (MAILBOX_OK == ret_val) {
         /*发送邮件*/
        ret_val = mailbox_send_buff(mb_buf);
    }

exit_out:
    /*释放邮箱buffer*/
    if (MAILBOX_NULL != mb_buf) { 
        mailbox_release_buff(mb_buf);
    }
    
    return ret_val;
}


/****************************************************************************
 函 数 名  : mailbox_read_msg_data
 功能描述  : 邮箱用户在数据接收回调函数中调用, 从邮箱中读取一封最先到达的邮件
 输入参数  : mail_handle -- 邮箱句柄, 数据接收回调函数入参
             buff      -- 保存待读出数据的缓存地址
             *size     -- 缓存长度, 单位byte, 需要大于待读取邮件长度
 输出参数  : *size     -- 实际读取长度, 单位byte
 返 回 值  : MAILBOX_OK / MAILBOX_ERRO
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月26日
    修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_GLOBAL unsigned long mailbox_read_msg_data(
                void                   *mail_handle,
                char                   *buff,
                unsigned long          *size)
{
    struct mb_queue *pMailQueue = (struct mb_queue *)mail_handle;

    if ((MAILBOX_NULL == pMailQueue) || (MAILBOX_NULL == buff) || (MAILBOX_NULL == size)) {
        return (unsigned long)mailbox_logerro_p1(MAILBOX_ERR_GUT_INPUT_PARAMETER, 0);
    }

    if (pMailQueue->size  >  *size) {
        return (unsigned long)mailbox_logerro_p1(MAILBOX_ERR_GUT_USER_BUFFER_SIZE_TOO_SMALL, *size);
    }

    /*检查用户传回的邮箱数据队列句柄的有效性*/
    if ((0 == pMailQueue->length) ||
        ((pMailQueue->front - pMailQueue->base) >  pMailQueue->length ) ||
        ((pMailQueue->rear - pMailQueue->base) >  pMailQueue->length )) {
        return (unsigned long)mailbox_logerro_p1(MAILBOX_CRIT_GUT_INVALID_USER_MAIL_HANDLE, pMailQueue);
    }

    *size =  mailbox_read_buff(pMailQueue, buff, pMailQueue->size);

    return MAILBOX_OK;
}

/*****************************************************************************
 函 数 名  : mailbox_send_msg
 功能描述  : 提供给各模块进行核间数据发送的接口。
 输入参数  :
             unsigned long       mailcode      -- 邮件的id号, 逻辑通道号。
             unsigned char      *data           -- 指向邮件数据的指针。
             unsigned long       length/byte     -- 数据或者消息总长度 字节为单位。
 输出参数  : 无
 返 回 值  : unsigned long
             成功OK, 异常返回值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月28日
    修改内容   : 新生成函数

*****************************************************************************/
MAILBOX_EXTERN unsigned long mailbox_send_msg(
                unsigned long            mailcode,
                void                    *data,
                unsigned long            length)
{
    unsigned long  ret_val;
    unsigned long  try_go_on = MAILBOX_TRUE;
    unsigned long  try_times = 0;

    ret_val= BSP_CPU_StateGet(mailbox_get_dst_id(mailcode));
    if(!ret_val)
    {
        return MAILBOX_TARGET_NOT_READY;
    }
    ret_val = mailbox_try_send_msg(mailcode, data, length);

    if (MAILBOX_FALSE == mailbox_int_context()) {
        /*发送满等待轮询尝试*/
        while (MAILBOX_FULL == ret_val) {
            mailbox_delivery(mailbox_get_channel_id(mailcode));
            try_go_on = mailbox_scene_delay(MAILBOX_DELAY_SCENE_MSG_FULL, &try_times);

            if (MAILBOX_TRUE == try_go_on) {
                ret_val = mailbox_try_send_msg(mailcode, data, length);
            } else {
                break;
            }
        }
    }

    if (MAILBOX_OK != ret_val) {
        /*mailbox_show(mailcode,0);*/
        /*mailbox_assert(ret_val);*/
        if (MAILBOX_FULL != ret_val) {
            ret_val = MAILBOX_ERRO;
        }
        return ret_val;
    }

    return ret_val;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

