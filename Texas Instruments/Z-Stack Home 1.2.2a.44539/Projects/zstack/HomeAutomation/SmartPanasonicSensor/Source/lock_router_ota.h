
#ifndef LOCK_ROUTER_OTA_H
#define LOCK_ROUTER_OTA_H

#ifdef __cplusplus
extern "C"
{
#endif


#define OTA_SPI_FLASH_INFO_VALID  0x55555555  /*image is valid*/
#define OTA_SPI_FLASH_INFO_INVALID  0xAAAAAAAA  /*image is invalid*/
#define OTA_SPI_FLASH_INFO_ADDR  0  /*save image info*/
#define OTA_SPI_FLASH_IMAGE_ADDR  8192
#define OTA_SPI_FLASH_PAGE_SIZE  256
#define OTA_SPI_FLASH_SECTOR_SIZE  4096
#define OTA_SPI_FLASH_SECTOR_SIZE_MASK  0xfffff000
#define OTA_PARM_LEN        12
#define OTA_PACKET_LEN  100


typedef struct {
    uint16 sw;
    uint16 hw;
    uint8 odd_or_even;
    uint8 dev_type;
}ota_ver_msg_t;

typedef enum ota_reply {
    OTA_SUCCEED=1,
    OTA_CHECK_FAIL,
    OTA_PARM_FAIL,
    OTA_CODE_FAIL,
    OTA_BATTERY_LOW
} ota_reply_t;

typedef struct setota_msg {
    uint16 seq;
    uint8 size;
    uint8 msg[OTA_PACKET_LEN];
}setota_msg_t;

typedef struct ota_info_msg {
   uint32 sw_v;
   uint32 size;
   uint32 crc;
}ota_info_msg_t;

typedef struct{
    uint32 curr_seq;
    uint32 curr_size;
    uint32 total_size;
    uint16 sw_ver;
    uint8 hw_ver[2];
    uint32 crc;
}ota_nv_info_t;

typedef struct {
    uint32 validflag;
    uint32 total_size;
    uint32 crc;
}ota_iamge_info_t;



uint16 get_hw_ver(void);
void save_hw_ver(uint8 *hw_ver);
uint16 get_version(uint8 *str);
uint16 get_sw_ver(void);
void make_crc32_table(void);
uint32 make_crc(uint32 crc, uint8 *string, uint32 size);
void ota_init(void);
void ota_info_load(void);
void ota_info_reset(void);
uint8 ota_info_save(void);
uint8 ota_crc_check(void);
uint16 ota_save_image_data(uint8 size, uint8 *data);
uint16 ota_save_image_info(uint32 validflag);
uint16 ota_param_msg_proc(uint8 size, uint8 *msg);
uint16 ota_data_msg_proc(uint32 recv_seq, uint8 size, uint8 *msg);
void ota_msg_check_crc(void);
void ota_notify(uint8 *pdata, uint32 len);
void ota_msg_proc(uint8 *pdata, uint32 len);
void int2str(uint8* str, uint32 intnum);

#endif

