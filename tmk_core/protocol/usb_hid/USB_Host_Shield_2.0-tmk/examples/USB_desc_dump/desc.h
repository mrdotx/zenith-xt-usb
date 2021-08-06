//
// Descriptor Types
//
// These are defined in usb_ch9.h
//#define USB_DESCRIPTOR_DEVICE                   0x01
//#define USB_DESCRIPTOR_CONFIGURATION            0x02
//#define USB_DESCRIPTOR_STRING                   0x03
//#define USB_DESCRIPTOR_INTERFACE                0x04
//#define USB_DESCRIPTOR_ENDPOINT                 0x05
//#define USB_DESCRIPTOR_DEVICE_QUALIFIER         0x06
//#define USB_DESCRIPTOR_OTHER_SPEED              0x07
//#define USB_DESCRIPTOR_INTERFACE_POWER          0x08
//#define USB_DESCRIPTOR_OTG                      0x09
// TODO: should be defined in usb_ch9.h
// Descriptor Types - USB3 spec 9.4
#define USB_DESCRIPTOR_DEBUG                    0x0A
#define USB_DESCRIPTOR_INTERFACE_ASSOCIATION    0x0B
#define USB_DESCRIPTOR_BOS                      0x0F
#define USB_DESCRIPTOR_DEVICE_CAPABILITY        0x10
#define USB_DESCRIPTOR_SS_USB_EP_COMPANION      0x30
#define USB_DESCRIPTOR_SSP_ISO_EP_COMPANION     0x31

typedef struct {
        uint8_t bLength;
        uint8_t bDescriptorType;
        uint16_t bcdUSB;
        uint8_t bDeviceClass;
        uint8_t bDeviceSubClass;
        uint8_t bDeviceProtocol;
        uint8_t bMaxPacketSize0;
        uint8_t bNumConfigurations;
        uint8_t bReserved;
} __attribute__((packed)) USB_DEVICE_QUALIFIER_DESCRIPTOR;


//
// Class
//
// https://www.usb.org/defined-class-codes
#define CLASS_AUDIO                         0x01
#define CLASS_CDC_CONTROL                   0x02
#define CLASS_HID                           0x03
#define CLASS_PHYSICAL                      0x05
#define CLASS_IMAGE                         0x06
#define CLASS_PRINTER                       0x07
#define CLASS_MASS_STORAGE                  0x08
#define CLASS_HUB                           0x09
#define CLASS_CDC_DATA                      0x0A
#define CLASS_SMART_CARD                    0x0B
#define CLASS_CONTENT_SECUIRITY             0x0D
#define CLASS_VIDEO                         0x0E
#define CLASS_PERSONAL_HEALTHCARE           0x0F

//  Class-Specific Descriptor Type
#define CS_DEVICE                           0x21
#define CS_CONFIGURATION                    0x22
#define CS_STRING                           0x23
#define CS_INTERFACE                        0x24
#define CS_ENDPOINT                         0x25
// MIDI 2.0
#define CS_GR_TRM_BLOCK                     0x26



//
// Audio
//
// https://www.usb.org/sites/default/files/audio10.pdf
// https://www.usb.org/document-library/usb-audio-devices-rev-30-and-adopters-agreement
// Interface SubClass
#define AUDIO_CONTROL                       0x01
#define AUDIO_STREAMING                     0x02
#define AUDIO_MIDI_STREAMING                0x03
// Interface Protocol
#define AUDIO_PROTOCOL_V2                   0x20
// Interface Descriptor Subtype AC
#define AUDIO_HEADER                        0x01
#define AUDIO_INPUT_TERMINAL                0x02
#define AUDIO_OUTPUT_TERMINAL               0x03
#define AUDIO_MIXER_UNIT                    0x04
#define AUDIO_SELECTOR_UNIT                 0x05
#define AUDIO_FEATURE_UNIT                  0x06
#define AUDIO_EFFECT_UNIT                   0x07
#define AUDIO_PROCESSING_UNIT               0x08
#define AUDIO_EXTENSION_UNIT                0x09
#define AUDIO_CLOCK_SOURCE                  0x0A
#define AUDIO_CLOCK_SELECTOR                0x0B
#define AUDIO_CLOCK_MULTIPLIER              0x0C
#define AUDIO_SAMPLE_RATE_CONVERTER         0x0D
// Interface Descriptor Subtype AS
#define AUDIO_AS_GENERAL                    0x01
#define AUDIO_FORMAT_TYPE                   0x02
#define AUDIO_ENCODER                       0x03
#define AUDIO_DECODER                       0x04
// Endpoint Descriptor Subtype
#define AUDIO_EP_GENERAL                    0x01

typedef struct {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bDescriptorSubtype;
  uint16_t bcdADC;
  uint8_t  bCategory;
  uint16_t wTotalLength;
  uint8_t  bmControls;
} __attribute__((packed)) AUDIO_AC_HEADER_DESC;



//
// MIDI
//
// https://www.usb.org/sites/default/files/midi10.pdf
// https://www.usb.org/sites/default/files/USB%20MIDI%20v2_0.pdf
// Interface Descriptor Subtype
#define MIDI_MS_HEADER                      0x01
#define MIDI_IN_JACK                        0x02
#define MIDI_OUT_JACK                       0x03
#define MIDI_ELEMENT                        0x04
// Endpoint Descriptor Subtype
#define MIDI_MS_GENERAL                     0x01
#define MIDI_MS_GENERAL_2_0                 0x02

typedef struct {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bDescriptorSubtype;
  uint16_t bcdMSC;
  uint16_t wTotalLength;
} __attribute__((packed)) MIDI_MS_HEADER_DESC;

typedef struct {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bDescriptorSubtype;
  uint8_t  bJackType;
  uint8_t  bJackID;
  uint8_t  iJack;
} __attribute__((packed)) MIDI_IN_JACK_DESC;

typedef struct {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bDescriptorSubtype;
  uint8_t  bJackType;
  uint8_t  bJackID;
  uint8_t  bNrInputPins;
  uint8_t  BaSourceID;
  uint8_t  BaSourcePin;
  uint8_t  iJack;
} __attribute__((packed)) MIDI_OUT_JACK_DESC;

typedef struct {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bDescriptorSubtype;
  uint8_t  bNumEmbMIDIJack;
  uint8_t  BaAssocJackID;
} __attribute__((packed)) MIDI_MS_GENERAL_DESC;
