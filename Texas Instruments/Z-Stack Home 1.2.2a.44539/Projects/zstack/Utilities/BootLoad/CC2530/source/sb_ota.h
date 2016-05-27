


#ifndef SB_OTA_H
#define SB_OTA_H



#define OTA_SPI_FLASH_INFO_VALID  0x55555555  /*image is valid*/
#define OTA_SPI_FLASH_INFO_INVALID  0xAAAAAAAA  /*image is invalid*/
#define OTA_SPI_FLASH_INFO_ADDR  0  /*image info address*/
#define OTA_SPI_FLASH_IMAGE_ADDR  8192  /*image data address*/


typedef struct {
    uint32 validflag;
    uint32 total_size;
    uint32 crc;
}ota_iamge_info_t;


uint8 sb_ota_upgrade(void);
void sb_ota_wirte_internal_image(uint32 address, uint8 *data, uint32 len);
void sb_ota_read_internal_image(uint32 address, uint8 *data, uint32 len);
uint32 sb_ota_crc(uint32 crc, uint8 *data, uint32 len);
uint8 sb_ota_check_image(void);
uint8 sb_ota_copy_image(void);
void ota_set_iamge_invalid(void);
void ota_debug_print(uint8 *str);

#endif




