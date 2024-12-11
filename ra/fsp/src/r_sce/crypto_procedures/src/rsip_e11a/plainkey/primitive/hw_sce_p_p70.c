/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_ra_private.h"

fsp_err_t HW_SCE_OemKeyIndexValidationSub (const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_6CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_70H, 0x00700001U);
    WR1_PROG(REG_4CH, 0x00000000U);

    HW_SCE_p_func049(InData_Cmd);

    WR1_PROG(REG_94H, 0x0000b440U);
    WR1_PROG(REG_94H, 0x0C8003A0U);

    HW_SCE_p_func056();

    HW_SCE_p_func100(0x744eb698U, 0x3978b211U, 0x0a8c0a57U, 0xdd149f18U);
    WR1_PROG(REG_40H, 0x00400000U);
    WR1_PROG(REG_24H, 0x00000000U);

    if (CHCK_STS(REG_40H, 22, 1))
    {
        HW_SCE_p_func102(0x63759f6dU, 0xc5be6001U, 0x7992cee5U, 0x2f7df327U);
        WR1_PROG(REG_6CH, 0x00000040U);
        WAIT_STS(REG_20H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_14H, 0x000000c7U);
        WR1_PROG(REG_9CH, 0x800100c0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, InData_KeyIndex[0]);
        WR1_PROG(REG_24H, 0x00000000U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000070U));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0x9cfc8e22U, 0x544594f6U, 0x3093dff4U, 0x38ef497fU);
        HW_SCE_p_func043();

        WR1_PROG(REG_94H, 0x000034c4U);

        WR1_PROG(REG_14H, 0x000000a7U);
        WR1_PROG(REG_9CH, 0x800100e0U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000070U));
        WR1_PROG(REG_24H, 0x00000000U);

        HW_SCE_p_func101(0xe8c1278cU, 0x9eca8bc2U, 0x7ab4a6a5U, 0xc409e0feU);
        HW_SCE_p_func044();

        WR1_PROG(REG_14H, 0x000000a1U);
        WR1_PROG(REG_D0H, 0x08000044U);
        WAIT_STS(REG_14H, 31, 1);
        WR1_PROG(REG_2CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_14H, 0x00020061U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0xf7009c06U);

        for (iLoop = 0U; iLoop < (KEY_INDEX_SIZE - 5); )
        {
            WAIT_STS(REG_14H, 31, 1);
            WR4_ADDR(REG_2CH, &InData_KeyIndex[1 + iLoop]);
            iLoop = iLoop + 4U;
        }

        HW_SCE_p_func205_r1();

        WR1_PROG(REG_14H, 0x000003c1U);
        WR1_PROG(REG_D4H, 0x40000000U);
        WR1_PROG(REG_D0H, 0x07008d05U);
        WAIT_STS(REG_14H, 31, 1);
        WR4_ADDR(REG_2CH, &InData_KeyIndex[1 + iLoop]);

        WR1_PROG(REG_D0H, 0x9c100005U);
        WR1_PROG(REG_00H, 0x00410011U);
        WAIT_STS(REG_04H, 30, 0);
        WR1_PROG(REG_40H, 0x00001800U);

        HW_SCE_p_func100(0x44514f8dU, 0x3e29cbabU, 0xd634c0e3U, 0x402c3a89U);
        WR1_PROG(REG_40H, 0x00400000U);
        WR1_PROG(REG_24H, 0x00000000U);

        if (CHCK_STS(REG_40H, 22, 1))
        {
            HW_SCE_p_func102(0xf521f8d8U, 0x762fd3a9U, 0x21105bd1U, 0xfb66ead9U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            HW_SCE_p_func102(0xabdb91cdU, 0xd5d27b10U, 0xe306bc34U, 0xfd5edb91U);
            WR1_PROG(REG_6CH, 0x00000040U);
            WAIT_STS(REG_20H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}