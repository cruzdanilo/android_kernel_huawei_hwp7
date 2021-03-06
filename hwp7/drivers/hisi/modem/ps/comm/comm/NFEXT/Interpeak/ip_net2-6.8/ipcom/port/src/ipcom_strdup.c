/*
 ******************************************************************************
 *                     INTERPEAK SOURCE FILE
 *
 *   Document no: @(#) $Name: VXWORKS_ITER18A_FRZ10 $ $RCSfile: ipcom_strdup.c,v $ $Revision: 1.8 $
 *   $Source: /home/interpeak/CVSRoot/ipcom/port/src/ipcom_strdup.c,v $
 *   $State: Exp $ $Locker:  $
 *
 *   INTERPEAK_COPYRIGHT_STRING
 *   Design and implementation by Lennart Bang <lob@interpeak.se>
 ******************************************************************************
 */


/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipcom_config.h"


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#define IPCOM_USE_CLIB_PROTO
#define IPCOM_DMALLOC_C
#include "ipcom_clib.h"


/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 6                    EXTERN PROTOTYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 7                    LOCAL PROTOTYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 8                    DATA
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 9                    STATIC FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 10                   GLOBAL FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 11                   PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    ipcom_strdup
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
#if defined(IPCOM_STRDUP) && IPCOM_STRDUP == 1
IP_PUBLIC char *
ipcom_strdup(const char *s1)
{
    char *s2;

    s2 = ipcom_malloc(ipcom_strlen(s1) + 1);
    if(s2 == IP_NULL)
        return IP_NULL;

    ipcom_strcpy(s2, s1);
    return s2;
}
#else
int ipcom_strdup_empty_file;
#endif


/*
***************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

