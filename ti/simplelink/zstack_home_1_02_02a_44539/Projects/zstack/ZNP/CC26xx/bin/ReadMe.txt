ZNP hex files for CC2630/50 are named as follows:

znp_(Coordinator|Router|EndDev)_pro[_secure][_linkkeyjoin].hex

===============================================================================
(Coordinator|Router|EndDev) : This component of the name identifies what type
of ZigBee device functionality this hex file supports.

_pro : Indicates support for Zigbee PRO

[_secure] : If present, this hex file is to be used with ZNP applications that 
use standard ZigBee security where the NWK key is sent in the clear or is 
pre-configured. When using this image, the host processor must register for 
specific ZDO callbacks using the ZDO_MSG_CB_REGISTER API, and will be notified 
of the response via the ZDO_MSG_CB_INCOMING command.

[_linkkeyjoin] : If present, this hex file is to be used with ZNP applications 
that use the Pre-configured Trust Center Link Key method of joining where the 
pre-configured trust center link key is used to encrypt the APS tunnel 
command which contains the NWK key. When using this image, the host processor 
must register for specific ZDO callbacks using the ZDO_MSG_CB_REGISTER API,
and will be notified of the response via the ZDO_MSG_CB_INCOMING command. 
===============================================================================
