

#include "OSAL.h"
#include "AF.h"
#include "OSAL_Nv.h"
#include "onboard.h"
#include "hal_ota.h"
#include <stdlib.h>
#include <string.h>
#include "hal_board_cfg.h"
#include "lock_router_app.h"
#include "lock_router_ota.h"
#include "router_print.h"

ota_nv_info_t ota_info = {0};
uint8 flag_crc_checked = false;
uint16 crc_check_ret = 0;
static const uint32 crc32_table[256]={
   0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
   0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
   0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
   0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
   0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
   0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
   0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
   0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924, 0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
   0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
   0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
   0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
   0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
   0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
   0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
   0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
   0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
   0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
   0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
   0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
   0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
   0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
   0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
   0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236, 0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
   0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
   0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
   0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
   0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
   0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
   0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
   0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
   0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
   0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94, 0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

extern uint8 lock_router_app_task_id;

void int2str(uint8* str, uint32 intnum)
{
    uint32 i, Div = 1000000000, j = 0, Status = 0;

    for (i = 0; i < 10; i++)
    {
        str[j++] = (intnum / Div) + 48;

        intnum = intnum % Div;
        Div /= 10;
        if ((str[j-1] == '0') & (Status == 0))
        {
            j = 0;
        }
        else
        {
            Status++;
        }
    }

    return ;
}

uint16 get_hw_ver(void)
{
    return ((ota_info.hw_ver[0]<<8)+ota_info.hw_ver[1]);
}

void save_hw_ver(uint8 *hw_ver)
{
    uint8 hd_ver[3] = {0};
    ota_nv_info_t ota_info_read = {0};

    osal_memcpy(&ota_info.hw_ver, hw_ver, 2);
    ota_info_save();
    osal_memcpy(&ota_info_read, &ota_info, sizeof(ota_nv_info_t));
    ota_info_load();
    if (osal_memcmp(&ota_info, &ota_info_read, sizeof(ota_nv_info_t)))
    {
        osal_memcpy(hd_ver, ota_info.hw_ver, 2);
        log_printf( "Hardware version = %s.\n", hd_ver);
    }
    else
    {
        log_printf( "Error: save hardware version error!\n");
    }

    return ;
}

uint16 get_version(uint8 *str)
{
    uint8 i = 0;
    uint8 ver[8] = {0};
    uint8 high = 0;
    uint8 low = 0;
    uint16 version = 0;

    strncpy((char*)ver, (const char*)str, 7);
    for (i=0;i<4;i++)
    {
        if (ver[i]=='.')
        {
            break;
        }
    }

    high = (unsigned char)atoi((const char*)ver);
    low = (unsigned char)atoi((const char*)(ver+i+1));
    version = (high << 8) | low;

    return version;
}


uint16 get_sw_ver(void)
{
    return get_version(SW_V);
}

uint32 make_crc(uint32 crc, uint8 *string, uint32 size)
{
    while(size--){
        crc = (crc >> 8)^(crc32_table[(crc ^ *string++)&0xff]);
    }
    return crc;
}

void ota_init(void)
{
    XNV_SPI_INIT();
    ota_info_load();
    return ;
}

void ota_info_load(void)
{
    if ( NV_OPER_FAILED != osal_nv_item_init (ZCD_NV_OTA_INFO, sizeof(ota_nv_info_t), NULL))
    {
        if (SUCCESS != osal_nv_read(ZCD_NV_OTA_INFO, 0, sizeof(ota_nv_info_t), &ota_info))
        {
            log_printf( "Error: read ota nv info error.\r\n");
        }
    }
    else
    {
        log_printf( "Error: init ota nv info error.\r\n");
    }

    return ;
}

void ota_info_reset(void)
{
    ota_info.curr_seq = 1;
    ota_info.curr_size = 0;
    ota_info.total_size = 0;
    osal_nv_write(ZCD_NV_OTA_INFO, 0, sizeof(ota_nv_info_t), &ota_info);

    return ;
}

uint8 ota_info_save(void)
{
    return osal_nv_write(ZCD_NV_OTA_INFO, 0, sizeof(ota_nv_info_t), &ota_info);
}

uint8 ota_crc_check(void)
{
    uint32 crc=0;
    uint32 cnt = 0;
    uint32 ota_flash_addr = OTA_SPI_FLASH_IMAGE_ADDR;
    uint32 len = 0;
    uint8 data[OTA_SPI_FLASH_PAGE_SIZE];

    while (cnt < ota_info.total_size)
    {
        len = (ota_info.total_size - cnt < OTA_SPI_FLASH_PAGE_SIZE) ? (ota_info.total_size - cnt) : OTA_SPI_FLASH_PAGE_SIZE;
        HalSPIRead(ota_flash_addr+cnt, data, len);
        crc = make_crc(crc, data, len);
        cnt += len;
    }

    if(crc != ota_info.crc)
    {
        log_printf("recv crc is %ld local crc is %ld\r\n", ota_info.crc, crc);
        return OTA_CHECK_FAIL;
    }

    return OTA_SUCCEED;
}

uint16 ota_save_image_data(uint8 size, uint8 *data)
{
    uint32 ota_flash_addr = OTA_SPI_FLASH_IMAGE_ADDR + ota_info.curr_size;
    uint8 data_read[OTA_PACKET_LEN] = {0};

    if (ota_info.curr_size == 0 || ota_flash_addr%OTA_SPI_FLASH_SECTOR_SIZE == 0)
    {
        HalSPIEraseSector(ota_flash_addr&OTA_SPI_FLASH_SECTOR_SIZE_MASK);
    }
    else if (ota_flash_addr%OTA_SPI_FLASH_SECTOR_SIZE + size >= OTA_SPI_FLASH_SECTOR_SIZE)
    {
        HalSPIEraseSector((ota_flash_addr + size)&OTA_SPI_FLASH_SECTOR_SIZE_MASK);
    }

    HalSPIWrite(ota_flash_addr, data, size);

    HalSPIRead(ota_flash_addr, data_read, size);

    if (osal_memcmp(data_read, data, size))
    {
        return OTA_SUCCEED;
    }
    else
        return OTA_CODE_FAIL;
}

uint16 ota_save_image_info(uint32 validflag)
{
    ota_iamge_info_t ota_image_info = {0};
    ota_iamge_info_t ota_image_info_read = {0};

    HalSPIEraseSector(OTA_SPI_FLASH_INFO_ADDR);

    ota_image_info.validflag = validflag;
    ota_image_info.total_size = ota_info.total_size;
    ota_image_info.crc = ota_info.crc;
    HalSPIWrite(OTA_SPI_FLASH_INFO_ADDR, (uint8*)&ota_image_info, sizeof(ota_iamge_info_t));

    HalSPIRead(OTA_SPI_FLASH_INFO_ADDR, (uint8*)&ota_image_info_read, sizeof(ota_iamge_info_t));
    if (osal_memcmp(&ota_image_info, &ota_image_info_read, sizeof(ota_iamge_info_t)))
        return OTA_SUCCEED;
    else
        return OTA_CODE_FAIL;
}

uint16 ota_param_msg_proc(uint8 size, uint8 *msg)
{
    ota_info_msg_t *info_msg = (ota_info_msg_t*)msg;

    if (size != OTA_PARM_LEN)
        return OTA_PARM_FAIL;

    ota_info.curr_size = 0;
    ota_info.total_size = info_msg->size;
    ota_info.sw_ver = info_msg->sw_v;
    ota_info.crc = info_msg->crc;

    log_printf("-set ota param -\r\n");
    log_printf("curr_seq = %ld, curr_size = %ld, total_size = %ld, crc = %ld.\r\n",
                    ota_info.curr_seq, ota_info.curr_size, ota_info.total_size, ota_info.crc);

    if (ota_info_save() != ZSuccess)
        return OTA_CODE_FAIL;

    if (ota_save_image_info(OTA_SPI_FLASH_INFO_INVALID) != OTA_SUCCEED)
    {
        log_printf("ERROR: save image info invalid fail.\r\n");
        return OTA_CODE_FAIL;
    }

    ota_info.curr_seq++;

    return OTA_SUCCEED;
}

uint16 ota_data_msg_proc(uint32 recv_seq, uint8 size, uint8 *msg)
{
    log_printf("-ota receive image-\r\n");
    log_printf("seq = %ld, curr_seq = %ld, size = %d, curr_size = %ld\r\n",
        recv_seq, ota_info.curr_seq, size, ota_info.curr_size);

    if (size > OTA_PACKET_LEN)
        return OTA_PARM_FAIL;

    if (recv_seq == ota_info.curr_seq)
    {
        if (ota_info.curr_size + size > ota_info.total_size)
        {
            log_printf("ERROR: size error\r\n");
            return OTA_CODE_FAIL;
        }

        if(ota_save_image_data(size, msg) != OTA_SUCCEED)
        {
            log_printf("ERROR: write image error\r\n");
            return OTA_CODE_FAIL;
        }

        ota_info.curr_size += size;
        if (ota_info.curr_size < ota_info.total_size)
        {
            ota_info.curr_seq++;
            //if(ota_info.curr_size % OTA_SPI_FLASH_SECTOR_SIZE == 0)
                //ota_info_save();
            log_printf("-ota receive image succeed-\r\n");
            return OTA_SUCCEED;
        }

        if (ota_info.curr_size == ota_info.total_size)
        {
            log_printf("---ota receive image complete---\r\n");
            flag_crc_checked = false;
            return OTA_SUCCEED;
        }
    }
    else if (recv_seq < ota_info.curr_seq)
    {
        log_printf("WARNNING: %ld seq is already received\r\n", recv_seq);
        return OTA_SUCCEED;
    }
    else
    {
        log_printf("ERROR: %ld seq is mising\r\n", ota_info.curr_seq);
        return OTA_CODE_FAIL;
    }

    return OTA_SUCCEED;
}

void ota_msg_check_crc(uint8 *pdata, uint32 len)
{
    uint16 ota_ret = 0;
    uint16 tid = 0;

    tid = pdata[3];
    tid = (tid << 8) | pdata[2];

    log_printf("--ota msg check crc---\r\n");

    if (flag_crc_checked == false && ota_info.curr_size != ota_info.total_size)
    {
        log_printf("Error: image not complete, curr_size=%ld, total_size=%ld\r\n", ota_info.curr_size, ota_info.total_size);
        ota_ret = OTA_CODE_FAIL;
    }
    else if (flag_crc_checked)
    {
        ota_ret = crc_check_ret;
    }
    else if (ota_crc_check() == OTA_SUCCEED)
    {
        if (ota_save_image_info(OTA_SPI_FLASH_INFO_VALID) == OTA_SUCCEED)
        {
            ota_info_reset();
            log_printf("---ota crc check succeed---\r\n");
            osal_start_timerEx(lock_router_app_task_id, LOCK_ROUTER_EVENT_OTA_RESET, 10000);
            ota_ret = OTA_SUCCEED;
        }
        else
        {
            log_printf("Error: save image info failed\r\n");
            ota_ret = OTA_CODE_FAIL;
        }
        flag_crc_checked = true;
        crc_check_ret = ota_ret;
    }
    else
    {
        ota_info.curr_seq = 1;
        ota_info.curr_size = 0;
        ota_info_save();
        ota_ret = OTA_CHECK_FAIL;
        flag_crc_checked = true;
        crc_check_ret = ota_ret;
    }

    log_printf("--ota msg check crc ota_ret = %d---\r\n", ota_ret);
    if (ota_ret == OTA_SUCCEED || ota_ret == OTA_CHECK_FAIL)
        send_msg_to_center((uint8*)&ota_ret, sizeof(uint16), MSG_TYPE_OTA_CRC_CHK, tid);

    return ;
}

void ota_notify(uint8 *pdata, uint32 len)
{
    uint16 new_ver = 0;
    uint16 tid = 0;
    ota_ver_msg_t lock_ver = {0};

    log_printf("--------- get ota version ----------.\r\n");

    if (len <= 4)
    {
        log_printf( "Error: get ota sw ver, len = %d.\r\n", len);
        return ;
    }

    new_ver = pdata[5];
    new_ver = (new_ver << 8) | pdata[4];
    tid = pdata[3];
    tid = (tid << 8) | pdata[2];

    lock_ver.hw = get_hw_ver();
    lock_ver.sw = get_sw_ver();
    lock_ver.odd_or_even = 0;
    //if (new_ver != ota_info.sw_ver)
        ota_info_reset();

    log_printf("lock hw = %d, sw = %d.\r\n", lock_ver.hw, lock_ver.sw);
    log_printf("last_ver = %d, new_ver = %d\r\n", ota_info.sw_ver, new_ver);

    send_msg_to_center((uint8 *)&lock_ver, sizeof(ota_ver_msg_t), MSG_TYPE_OTA_GET_SW_VER, tid);
}

void ota_msg_proc(uint8 *pdata, uint32 len)
{
    uint16 ota_ret = 0;
    uint16 ota_seq[2] = {0};
    uint16 tid = 0;
    setota_msg_t ota_code = {0};

    tid = pdata[3];
    tid = (tid << 8) | pdata[2];
    osal_memcpy(&ota_code, &pdata[4], sizeof(setota_msg_t));

    log_printf("ota msg seq=%d, curr_seq=%ld, size=%d, tid=%d.\r\n", ota_code.seq, ota_info.curr_seq, ota_code.size, tid);

    if (ota_code.seq == 0)
    {
        ota_seq[0] = OTA_SUCCEED;
        ota_seq[1] = ota_info.curr_seq;
        send_msg_to_center((uint8*)&ota_seq, sizeof(ota_seq), MSG_TYPE_OTA_MSG, tid);
        return ;
    }
    else if (ota_code.seq == 1)
        ota_ret = ota_param_msg_proc(ota_code.size, ota_code.msg);
    else
        ota_ret = ota_data_msg_proc(ota_code.seq, ota_code.size, ota_code.msg);

    log_printf("ota msg ret = %d.\r\n", ota_ret);

    if (ota_ret == OTA_SUCCEED || ota_ret == OTA_CHECK_FAIL)
        send_msg_to_center((uint8*)&ota_ret, sizeof(uint16), MSG_TYPE_OTA_MSG, tid);

    return ;
}




