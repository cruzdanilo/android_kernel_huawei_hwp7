/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : drv_mailbox_port_linux.h
  �� �� ��   : ����
  ��������   : 2012��9��24��
  ����޸�   :
  ��������   : mailbox C��  linuxƽ̨ϵͳʵ������ͷ�ļ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2012��9��24��
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _DRV_MAILBOX_PORT_LINUX_H_
#define _DRV_MAILBOX_PORT_LINUX_H_


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*��ʵ��ַת���ӿڶ���*/
#ifndef _DRV_LLT_
#include <mach/hardware.h>

/*ACPUʵ��ַ�������ַӳ���ת���ӿ�*/
#define MEM_CORE_SHARE_PHY2VIRT(phy)         (((unsigned int)phy) - IPC_SHARE_MEM_ADDR + IPC_SHARE_MEM_VIRT_ADDR)
#define MEM_CORE_SHARE_VIRT2PHY(virt)        (((unsigned int)virt) - IPC_SHARE_MEM_VIRT_ADDR + IPC_SHARE_MEM_ADDR)

#else

/*ACPUʵ��ַ�������ַӳ���ת���ӿ�*/
#define MEM_CORE_SHARE_PHY2VIRT(phy)         (phy)
#define MEM_CORE_SHARE_VIRT2PHY(virt)        (virt)
#endif

/*����ͨ�������ܣ��˵�������ýӿڶ���*/
/*������CPU��ID*/
#define MAILBOX_LOCAL_CPUID                         MAILBOX_CPUID_ACPU

/*����C��ƽ̨��ص� ����ͨ�� �����������շ�ͨ�� */
#define MAILBOX_CHANNEL_NUM \
    ( MAILBOX_CHANNEL_BUTT(ACPU, HIFI)   \
    + MAILBOX_CHANNEL_BUTT(ACPU, MCU)    \
    + MAILBOX_CHANNEL_BUTT(ACPU, CCPU)   \
    + MAILBOX_CHANNEL_BUTT(HIFI, ACPU)   \
    + MAILBOX_CHANNEL_BUTT(MCU,  ACPU)   \
    + MAILBOX_CHANNEL_BUTT(CCPU,  ACPU)  \
    )

/*����C��ƽ̨��ص� �ʼ� ���� , ֻ���Ľ���ͨ��*/
#define MAILBOX_USER_NUM    \
    ( MAILBOX_USER_BUTT(HIFI, ACPU, MSG) \
    + MAILBOX_USER_BUTT(MCU,  ACPU, MSG) \
    + MAILBOX_USER_BUTT(CCPU,  ACPU, MSG) \
    + MAILBOX_USER_BUTT(CCPU,  ACPU, IFC) \
    + MAILBOX_USER_BUTT(MCU,  ACPU, IFC) \
    )

/*��ӡ���������ö���*/
/*����̨��ӡ����ӿ�*/
#ifdef _DRV_LLT_
#define mailbox_out(p)                              (printf p)
#else
#define mailbox_out(p)                              (printk p)
#endif

/*���������Ƿ��ӡ����*/
#define _MAILBOX_LINE_                              __LINE__

/*���������Ƿ��ӡ�ļ���,(����ӡ�ļ����ɽ�ʡ����ռ�)*/
#define _MAILBOX_FILE_                              (void*)(0) /*__FILE__*/

#define MAILBOX_LOG_LEVEL                           MAILBOX_LOG_INFO 


/*������Թ���������ö���*/
/*�����ڴ�CPU�ϴ򿪿�ά�ɲ⹦��*/
#ifndef MAILBOX_OPEN_MNTN
#define MAILBOX_OPEN_MNTN
#endif

/*��ά�ɲ��¼�������ID��*/
#define MAILBOX_RECORD_USEID_NUM                    (64)

#define RT  "\n"   /*��ӡ�س�����*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /*_DRV_MAILBOX_LINUX_H_*/
