/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : AtMuxInterface.h
  版 本 号   : 初稿
  生成日期   : 2012年8月10日
  最近修改   :
  功能描述   : AT模块同MUX模块的接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月10日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __ATMUXINTERFACE_H__
#define __ATMUXINTERFACE_H__


/*****************************************************************************
      1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  1 消息头定义
*****************************************************************************/


/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
枚举名    : AT_MUX_DLCI_TYPE_ENUM
枚举说明  : AT同MUX之间的端口类型
            DLCI1<->HSIC端口14, 音频切换端口
            DLCI2<->HSIC端口15, AGPS端口
            DLCI3<->HSIC端口16, FELICA/NFC端口
            DLCI4<->HSIC端口17, ISDB端口
  1.日    期   : 2012年8月10日
    修改内容   : V7R1C50 MUX项目新增
*****************************************************************************/
enum AT_MUX_DLCI_TYPE_ENUM
{
    AT_MUX_DLCI1_ID                 = 1, /* 链路号1，对应HSIC端口14, 音频切换端口 */
    AT_MUX_DLCI2_ID                 = 2, /* 链路号2，对应HSIC端口15, AGPS端口 */
    AT_MUX_DLCI3_ID                 = 3, /* 链路号3，对应HSIC端口16, FELICA/NFC端口 */
    AT_MUX_DLCI4_ID                 = 4, /* 链路号4，对应HSIC端口17, ISDB端口 */
    AT_MUX_DLCI5_ID                 = 5, /* 链路号5 */
    AT_MUX_DLCI6_ID                 = 6, /* 链路号6 */
    AT_MUX_DLCI7_ID                 = 7, /* 链路号7 */
    AT_MUX_DLCI8_ID                 = 8, /* 链路号8 */
    AT_MUX_DLCI9_ID                 = 9, /* 链路号9 */
    AT_MUX_DLCI10_ID                = 10, /* 链路号10 */
    AT_MUX_DLCI11_ID                = 11, /* 链路号11 */
    AT_MUX_DLCI12_ID                = 12, /* 链路号12 */
    AT_MUX_DLCI13_ID                = 13, /* 链路号13 */
    AT_MUX_DLCI14_ID                = 14, /* 链路号14 */
    AT_MUX_DLCI15_ID                = 15, /* 链路号15 */
    AT_MUX_DLCI16_ID                = 16, /* 链路号16 */

    AT_MUX_DLCI_TYPE_BUTT           = 65  /*链路号最多到64号 */
};
typedef VOS_UINT8 AT_MUX_DLCI_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  6 消息定义
*****************************************************************************/

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32 MUX_DlciDlDataSend (AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci, VOS_UINT8* pData, VOS_UINT16 usDataLen);

typedef VOS_UINT32 (*RCV_UL_DLCI_DATA_FUNC)(AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci, VOS_UINT8* pData, VOS_UINT16 usDataLen);

VOS_UINT32 MUX_AtRgstUlPortCallBack (AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci, RCV_UL_DLCI_DATA_FUNC pFunc);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif


