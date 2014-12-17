/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasSms.h
  �� �� ��   : ����
  ��������   : 2008��2��22��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��2��22��
    �޸�����   : �����ļ�
 2.��    ��   : 2009��3��23��
   �޸�����   : AT2D08752, W���뷽ʽ�£��źŽ���ʱ�������Ͷ������Ż�����Գ��ַ��Ͳ���ʧ�ܣ�
 3.��    ��   : 2011��04��23��
   �޸�����   : for V7R1 porting, ȥ��ö�ٳ�Ա���Ķ��ţ��������WARNING
******************************************************************************/
#ifndef __NASSMS_H__
#define __NASSMS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"



#pragma pack(4)

/*****************************************************************************
  2 ��������
*****************************************************************************/

/*------------------------ TP Message type indicator (MTI) 23.040-------------------*/
#define NAS_SMS_TP_MTI_SUBMIT                              (0x01)               /* SMS-SUBMIT        */
#define NAS_SMS_TP_MTI_MASK                                (3)
#define NAS_SMS_TI_FLAG_MASK                               (0x80)
#define NAS_SMS_TI_VALUE_MASK                              (0x70)
#define NAS_SMS_LOCAL_TI_VALUE_MASK                        (0x07)
#define NAS_SMS_TI_VALUE_OFFSET                            (4)
#define NAS_SMS_TI_FLAG_OFFSET                             (7)


/*------------------------------------------------------------------------------*/
/*------------------------Message type indicator (MTI) 24.011-------------------*/
/*------------------------------------------------------------------------------*/
#define MN_MSG_RP_MTI_UP_RP_DATA                            0x00                /* ms -> n RP-DATA */
#define MN_MSG_RP_MTI_UP_RP_ACK                             0x02                /* ms -> n RP-ACK  */
#define MN_MSG_RP_MTI_UP_RP_ERR                             0x04                /* ms -> n RP-ERROR*/
#define MN_MSG_RP_MTI_UP_RP_SMMA                            0x06                /* ms -> n RP-SMMA */
#define MN_MSG_RP_MTI_DOWN_RP_DATA                          0x01                /* n -> ms RP-DATA */
#define MN_MSG_RP_MTI_DOWN_RP_ACK                           0x03                /* n -> ms RP-ACK  */
#define MN_MSG_RP_MTI_DOWN_RP_ERR                           0x05                /* n -> ms RP-ERROR*/
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
#define  MN_MSG_RP_USER_DATA_IEI                            0x41                /* User data iei  */

#define SMT_SMR_ABORT_FLG_EXIST         1
#define SMT_SMR_ABORT_FLG_NO_EXIST      0

/* Deleted by f62575 for V9R1 STK����, 2013-6-26, begin */
/* Deleted SMS_RP_RPT_STATUS_ENUM */
/* Deleted by f62575 for V9R1 STK����, 2013-6-26, end */

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/
/* ԭ�������� */
typedef enum
{
    SMT_SMR_DATA_REQ,
    SMT_SMR_REPORT_REQ,
    SMT_SMR_SMMA_REQ,
    SMT_SMR_CP_ACK_REQ,
    SMT_SMR_MAX
}SMT_SMR_REQ_ENUM;
typedef VOS_UINT32 SMT_SMR_REQ_ENUM_U32;

/* Deleted by f62575 for V9R1 STK����, 2013-6-26, begin */
/* Del SMR_SMT_ERR_TYPE_ENUM_UINT8 */
/* Deleted by f62575 for V9R1 STK����, 2013-6-26, end */

typedef enum
{
    SMR_SMT_ATTACH_IND,
    SMR_SMT_DATA_IND,
    SMR_SMT_REPORT_IND,
    SMR_SMT_LINK_CLOSE_IND,
    SMR_SMT_MT_ERR_IND,
    SMR_SMT_MAX
}SMR_SMT_IND_ENUM;
typedef VOS_UINT32 SMR_SMT_IND_ENUM_U32;

/* ԭ��SMT_SMR_DATA_REQ,SMT_SMR_REPORT_REQ�Ľṹ�� */
typedef struct
{

    VOS_MSG_HEADER                                                              /*��Ϣͷ*/
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulDataLen;                              /*�û����ݵĳ���*/
    VOS_UINT8                           aucData[4];                           /*�û����ݵ�ַ*/
}SMT_SMR_DATA_STRU;

/* ʹ��ԭ��SMR_SMT_DATA_IND����EST_INDʱ�Ľṹ�壬���������� */
typedef struct
{

    VOS_MSG_HEADER                                                              /*��Ϣͷ*/
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulDataLen;                              /*�û����ݵĳ���*/
    VOS_UINT8                           ucRcvDomain;                            /*������*/
    VOS_UINT8                           aucReserve[3];                          /*����λ*/
    VOS_UINT8                           aucData[4];                             /*�û����ݵ�ַ*/
}SMR_SMT_EST_IND_STRU;

typedef struct
{
    VOS_UINT8                           ucDomain;
    VOS_UINT8                           aucReserve1[3];
    VOS_BOOL                            bAttachFlag;
}SMR_SMT_ATTACH_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /*��Ϣͷ*/
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulDataLen;                              /*�û����ݵĳ���*/
    VOS_UINT8                           aucData[256];                           /*�û����ݵ�ַ*/
}SMT_SMR_DATA_TEMP_STRU;
/* ԭ��SMT_SMR_SMMA_REQ�Ľṹ�� */
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ              */
    VOS_UINT32                          ulMsgName;
    VOS_UINT8                           ucAbortFlg;                             /* �Ƿ�Я��abort����    */
    VOS_UINT8                           ucSendDomain;
    VOS_UINT8                           aucReserve1[2];
}SMT_SMR_SMMA_STRU;

/*****************************************************************************
 ö����    : SMR_SMT_ERROR_ENUM
 �ṹ˵��  : TAF��SMS�Ľӿڴ�����
             0              �޴��󣬽����ڶ���������������ͳɹ�
             1        - 0x100  �ڲ�������
             0x20000  - 0x200FF  CP-ERROR��Ϣ�����룬��SMR_SMT_ERROR_CP_ERROR_BEGIN��CP-ERROR�տ���Ϣ�Ĵ�����(��8BIT)���
             0x40000  - 0x400FF  RP-ERROR��Ϣ�����룬��SMR_SMT_ERROR_RP_ERROR_BEGIN��RP-ERROR�տ���Ϣ�Ĵ�����(��8BIT)���
             0x80000  - 0x800FF  CS��ͨ�������룬��SMR_SMT_ERROR_CS_ERROR_BEGIN��MM�ϱ���ϢMMSMS_REL_IND�Ĵ�����(��8BIT)���
             0x100000 - 0x1000FF  PS��ͨ�������룬��SMR_SMT_ERROR_PS_ERROR_BEGIN��GMM�ϱ���ϢPMMSMS_ERROR_IND�Ĵ�����(��8BIT)���
             0x200000 - 0x2000FF  EPS��ͨ�������룬��SMR_SMT_ERROR_EPS_ERROR_BEGIN��GMM�ϱ���ϢID_LMM_SMS_ERR_IND�Ĵ�����(��8BIT)���
             0x400000 - 0x400FFF  IMS�����룬��SMR_SMT_ERROR_IMS_ERROR_BEGIN��IMS�ڲ�������(��12BIT)���

             
1.��    ��   : 2013��6��26��
  �޸�����   : V9R1 STK�������´���
2.��    ��   : 2013��9��16��
  �޸�����   : ����IMSA�ӿڣ�����IMS MSG�ڲ�cause

*****************************************************************************/
enum SMR_SMT_ERROR_ENUM
{
    SMR_SMT_ERROR_NO_ERROR                = 0x000000,

    SMR_SMT_ERROR_STATE_NOT_COMPATIBLE    = 0x000001,

    SMR_SMT_ERROR_NO_SERVICE              = 0x000002,

    SMR_SMT_ERROR_TC1M_TIMEOUT            = 0x000003,

    SMR_SMT_ERROR_TR1M_TIMEOUT            = 0x000004,

    SMR_SMT_ERROR_TR2M_TIMEOUT            = 0x000005,

    SMR_SMT_ERROR_USER_ABORT              = 0x000006,

    SMR_SMT_ERROR_CP_ERROR_BEGIN          = 0x020000,

    SMR_SMT_ERROR_RP_ERROR_BEGIN          = 0x040000,

    SMR_SMT_ERROR_CS_ERROR_BEGIN          = 0x080000,

    SMR_SMT_ERROR_PS_ERROR_BEGIN          = 0x100000,

    SMR_SMT_ERROR_EPS_ERROR_BEGIN         = 0x200000,

    SMR_SMT_ERROR_IMS_ERROR_BEGIN         = 0x400000,

    SMR_SMT_ERROR_IMSA_ERROR_BEGIN        = 0x800000,

    SMR_SMT_ERROR_ERROR_BUTT              = 0xFFFFFFFF
};
typedef VOS_UINT32 SMR_SMT_ERROR_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : SMR_SMT_MT_ERR_STRU
 �ṹ˵��  : SMS��TAF�ϱ��Ķ��Ż�����״̬�������ʧ����Ϣ�ṹ��
  1.��    ��   : 2013��6��26��
    �޸�����   : V9R1 STK�������´���
*****************************************************************************/
typedef struct
{

    VOS_MSG_HEADER                                                              /*��Ϣͷ*/
    VOS_UINT32                          ulMsgName;
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode;
}SMR_SMT_MT_ERR_STRU;

/* TPDU����󳤶ȣ��ο�Э��24011 8.2.5.3 */
#define SMR_SMT_RP_USER_DATA_LENGTH     (232)

/*****************************************************************************
 �ṹ��    : SMR_SMT_RPDU_STRU
 �ṹ˵��  : SMS��TAF�ϱ��Ķ��ŷ��ͽ����Ϣ�е�RPDU�ṹ
  1.��    ��   : 2013��6��26��
    �޸�����   : V9R1 STK�������´���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDataLen;                              /*�û����ݵĳ���*/
    VOS_UINT8                           aucData[SMR_SMT_RP_USER_DATA_LENGTH];   /*�û����ݵ�ַ*/
}SMR_SMT_RPDU_STRU;

/*****************************************************************************
 �ṹ��    : SMR_SMT_MO_REPORT_STRU
 �ṹ˵��  : SMS��TAF�ϱ��Ķ��ŷ��ͽ����Ϣ�ṹ��
             ucRpMr      RP-MR
             enErrorCode ���Ż���������ʧ��ԭ��ֵ�����ͳɹ�ΪSMR_SMT_ERROR_NO_ERROR
             stRpduData  SMS��TAF�ϱ��Ķ��ŷ��ͽ����Ϣ�е�RPDU�ṹ
                         enErrorCodeΪSMR_SMT_ERROR_RP_ERROR_BEGIN��SMR_SMT_ERROR_NO_ERRORʱ��Ч
  1.��    ��   : 2013��6��26��
    �޸�����   : V9R1 STK�������´���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*��Ϣͷ*/
    VOS_UINT32                          ulMsgName;
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode;
    SMR_SMT_RPDU_STRU                   stRpduData;                             /* ���Ż��������ͳɹ�����յ�RP-ERRORʱ��Ч */
}SMR_SMT_MO_REPORT_STRU;

/*****************************************************************************
  4 �궨��
*****************************************************************************/


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/


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

#endif /* __NASSMS_H__ */
