#include <usbhub.h>
#include <usbhid.h>
#include <hidescriptorparser.h>
#include "desc.h"


// This gets USB descriptors and shows in HEX dump and human readable output.
//
// Following descriptors are supported.
//
// - Device Descriptor
// - Configuration Descriptor
//     - Interface Descriptor
//     - Endpoint Descriptor
//     - HID Descriptor
// - HID Report descriptor
// - String Descriptor
// - Device Qualifier*
// - Other Speed*
// - Audio/MIDI Class*
// *: partly supported


// NOTE: Disable print options below when short of flash or memory space

// Parse and print descriptor
#ifndef NO_PRINT_DESC
#define PRINT_DESC
#endif

// Parse and print high-speed Hub descriptor
// To get descriptor of hub see NOTE of USBHub below
#ifndef NO_PRINT_DESC_HSHUB
//#define PRINT_DESC_HSHUB
#endif

// Parse and print HID Report descriptor
#ifndef NO_PRINT_DESC_REPORT
#define PRINT_DESC_REPORT
#endif



// https://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments
#define GET_MACRO(_0, _1, NAME, ...) NAME

// xprintln() and xprintln(s) can be allowed
#define _xprintln_0()       Serial.println()
#define _xprintln_1(s)      Serial.println(F(s))
#define xprintln(...)       GET_MACRO(_0, ##__VA_ARGS__, _xprintln_1, _xprintln_0)(__VA_ARGS__)

#define xprint(s)           Serial.print(F(s))

#define printVal(n, v)      _printVal(F(n ": "), v)
#define printValC(n, v)     _printVal(F("// " n ": "), v)
#define printDesc(n, v)     _printVal(F(n), v)
#define printDescC(n, v)    _printVal(F("// " n), v)


USB     Usb;
// NOTE: Comment out USBHub lines to get descriptors of hub, it doesn't work as a hub in that case
USBHub  hub1(&Usb);
USBHub  hub2(&Usb);

#define BUF_SIZE 512
uint8_t buf[BUF_SIZE];
EpInfo epInfo[1];

#define LANGID_SIZE 3
uint16_t langid[LANGID_SIZE];


void printHEX(uint8_t hex)
{
  if (hex < 16) Serial.print(F("0"));
  Serial.print(hex, HEX);
}

void printHEX(uint16_t hex)
{
  printHEX((uint8_t)(hex>>8));
  printHEX((uint8_t)hex);
}

void _printVal(const __FlashStringHelper *name, uint8_t hex)
{
  Serial.print(name); printHEX(hex); Serial.println();
}

void _printVal(const __FlashStringHelper *name, uint16_t hex)
{
  Serial.print(name); printHEX(hex); Serial.println();
}

void printError(uint8_t rcode)
{
  printVal("ERROR", rcode);
}

void dumpBuf(int len, uint8_t* buf, bool commented = false)
{
  for (int i = 0; i < len; i++) {
    if (i % 16)
      Serial.print(" ");
    else {
      if (i != 0) Serial.println();
      if (commented) Serial.print(F("// "));
    }

    printHEX(buf[i]);
  }
  Serial.println();
}

class dumpCallback : public USBReadParser {
public:
  void Parse(const uint16_t len, const uint8_t *pbuf, const uint16_t &offset) {
    for (int i = 0; i < len; i++) {
      if ((offset + i) % 16)
        Serial.print(" ");
      else {
        if ((offset + i) != 0) Serial.println();
      }

      printHEX(pbuf[i]);
    }
  }
} dumper;

#ifdef PRINT_DESC
void printUnknownDesc(uint8_t *p)
{
  xprint("\r\n// Unknown Desc: type: "), printHEX(*(p+1)); printVal(" len", *p);
  dumpBuf(*p, p);
}
void printDeviceDesc(USB_DEVICE_DESCRIPTOR *pD)
{
  printDesc("bLength:\t\t",             pD->bLength);
  printDesc("bDescriptorType:\t",       pD->bDescriptorType);
  printDesc("bcdUSB:\t\t\t",            pD->bcdUSB);
  printDesc("bDeviceClass:\t\t",        pD->bDeviceClass);
  printDesc("bDeviceSubClass:\t",       pD->bDeviceSubClass);
  printDesc("bDeviceProtocol:\t",       pD->bDeviceProtocol);
  printDesc("bMaxPacketSize0:\t",       pD->bMaxPacketSize0);
  printDesc("idVendor:\t\t",            pD->idVendor);
  printDesc("idProduct:\t\t",           pD->idProduct);
  printDesc("bcdDevice:\t\t",           pD->bcdDevice);
  printDesc("iManufacturer:\t\t",       pD->iManufacturer);
  printDesc("iProduct:\t\t",            pD->iProduct);
  printDesc("iSerialNumber:\t\t",       pD->iSerialNumber);
  printDesc("bNumConfigurations:\t",    pD->bNumConfigurations);
}
#ifdef PRINT_DESC_HSHUB
void printDeviceQualifierDesc(USB_DEVICE_QUALIFIER_DESCRIPTOR *pD)
{
  printDesc("bLength:\t\t",             pD->bLength);
  printDesc("bDescriptorType:\t",       pD->bDescriptorType);
  printDesc("bcdUSB:\t\t\t",            pD->bcdUSB);
  printDesc("bDeviceClass:\t\t",        pD->bDeviceClass);
  printDesc("bDeviceSubClass:\t",       pD->bDeviceSubClass);
  printDesc("bDeviceProtocol:\t",       pD->bDeviceProtocol);
  printDesc("bMaxPacketSize0:\t",       pD->bMaxPacketSize0);
  printDesc("bNumConfigurations:\t",    pD->bNumConfigurations);
  printDesc("bReserved:\t\t",           pD->bReserved);
}
#endif
void printConfigDesc(USB_CONFIGURATION_DESCRIPTOR *pC)
{
  printDesc("bLength:\t\t",             pC->bLength);
  printDesc("bDescriptorType:\t",       pC->bDescriptorType);
  printDesc("wTotalLength:\t\t",        pC->wTotalLength);
  printDesc("bNumInterfaces:\t\t",      pC->bNumInterfaces);
  printDesc("bConfigurationValue:\t",   pC->bConfigurationValue);
  printDesc("iConfiguration:\t\t",      pC->iConfiguration);
  printDesc("bmAttributes:\t\t",        pC->bmAttributes);
  printDesc("bMaxPower:\t\t",           pC->bMaxPower);
}
void printEndpointDesc(USB_ENDPOINT_DESCRIPTOR *pB)
{
  printDesc("bLength:\t\t",             pB->bLength);
  printDesc("bDescriptorType:\t",       pB->bDescriptorType);
  printDesc("bEndpointAddress:\t",      pB->bEndpointAddress);
  printDesc("bmAttributes:\t\t",        pB->bmAttributes);
  printDesc("wMaxPacketSize:\t\t",      pB->wMaxPacketSize);
  printDesc("bInterval:\t\t",           pB->bInterval);
}
void printInterfaceDesc(USB_INTERFACE_DESCRIPTOR *pI)
{
  printDesc("bLength:\t\t",             pI->bLength);
  printDesc("bDescriptorType:\t",       pI->bDescriptorType);
  printDesc("bInterfaceNumber:\t",      pI->bInterfaceNumber);
  printDesc("bAlternateSetting:\t",     pI->bAlternateSetting);
  printDesc("bNumEndpoints:\t\t",       pI->bNumEndpoints);
  printDesc("bInterfaceClass:\t",       pI->bInterfaceClass);
  printDesc("bInterfaceSubClass:\t",    pI->bInterfaceSubClass);
  printDesc("bInterfaceProtocol:\t",    pI->bInterfaceProtocol);
  printDesc("iInterface:\t\t",          pI->iInterface);
}
void printHIDDesc(USB_HID_DESCRIPTOR *pH)
{
  printDesc("bLength:\t\t",             pH->bLength);
  printDesc("bDescriptorType:\t",       pH->bDescriptorType);
  printDesc("bcdHID:\t\t\t",            pH->bcdHID);
  printDesc("bCountryCode:\t\t",        pH->bCountryCode);
  printDesc("bNumDescriptors:\t",       pH->bNumDescriptors);

  uint8_t *p = (uint8_t *)pH;
  for (int i = 6; i < pH->bLength; i = i + 3) {
    printDesc("bDescrType:\t\t",        *(p + i));
    printDesc("wDescriptorLength:\t",   (uint16_t)(*(p + i + 1)));
  }
}
void printAudioControlInterfaceDesc(uint8_t *p)
{
  uint8_t len = *p;
  uint8_t type = *(p+1);
  uint8_t subtype = *(p+2);
  xprint("\r\n// Audio Control Inteface:");
  switch (subtype) {
    case AUDIO_HEADER: {
      xprintln(" HEADER");
      AUDIO_AC_HEADER_DESC *pAH = (AUDIO_AC_HEADER_DESC *)p;
      printDesc("bLength:\t\t",             len);
      printDesc("bDescriptorType:\t",       type);
      printDesc("bDescriptorSubType:\t",    subtype);
      printDesc("bcdADC:\t\t\t",            pAH->bcdADC);
      printDesc("bCategory:\t\t",           pAH->bCategory);
      printDesc("wTotalLength:\t\t",        pAH->wTotalLength);
      printDesc("bmControls:\t\t",          pAH->bmControls);
      break;
    }
    default:
      printUnknownDesc(p);
      break;
  }
}
void printMIDIStreamingInterfaceDesc(uint8_t *p)
{
  uint8_t len = *p;
  uint8_t type = *(p+1);
  uint8_t subtype = *(p+2);
  xprint("\r\n// MIDI Streaming Inteface:");
  switch (subtype) {
    case MIDI_MS_HEADER: {
      xprintln(" HEADER");
      MIDI_MS_HEADER_DESC *pMH = (MIDI_MS_HEADER_DESC *)p;
      printDesc("bLength:\t\t",             len);
      printDesc("bDescriptorType:\t",       type);
      printDesc("bDescriptorSubType:\t",    subtype);
      printDesc("bcdMSC:\t\t\t",            pMH->bcdMSC);
      printDesc("wTotalLength:\t\t",        pMH->wTotalLength);
      break;
    }
    case MIDI_IN_JACK: {
      xprintln(" IN_JACK");
      MIDI_IN_JACK_DESC *pIJ = (MIDI_IN_JACK_DESC *)p;
      printDesc("bLength:\t\t",             len);
      printDesc("bDescriptorType:\t",       type);
      printDesc("bDescriptorSubType:\t",    subtype);
      printDesc("bJackType:\t\t",           pIJ->bJackType);
      printDesc("JackID:\t\t\t",            pIJ->bJackID);
      printDesc("iJack:\t\t\t",             pIJ->iJack);
      break;
    }
    case MIDI_OUT_JACK: {
      xprintln(" OUT_JACK");
      MIDI_OUT_JACK_DESC *pOJ = (MIDI_OUT_JACK_DESC *)p;
      printDesc("bLength:\t\t",             len);
      printDesc("bDescriptorType:\t",       type);
      printDesc("bDescriptorSubType:\t",    subtype);
      printDesc("bJackType:\t\t",           pOJ->bJackType);
      printDesc("JackID:\t\t\t",            pOJ->bJackID);
      printDesc("bNrInputPins:\t\t",        pOJ->bNrInputPins);
      printDesc("BaSourceID:\t\t",          pOJ->BaSourceID);
      printDesc("BaSourcePin:\t\t",         pOJ->BaSourcePin);
      printDesc("iJack:\t\t\t",             pOJ->iJack);
      break;
    }
    default:
      printUnknownDesc(p);
      break;
  }
}
void printMIDIStreamingEndpointDesc(uint8_t *p)
{
  uint8_t len = *p;
  uint8_t type = *(p+1);
  uint8_t subtype = *(p+2);
  xprint("\r\n// MIDI Streaming Endpoint:");
  switch (subtype) {
    case MIDI_MS_GENERAL: {
      xprintln(" GENERAL");
      MIDI_MS_GENERAL_DESC *pMG = (MIDI_MS_GENERAL_DESC *)p;
      printDesc("bLength:\t\t",             len);
      printDesc("bDescriptorType:\t",       type);
      printDesc("bDescriptorSubType:\t",    subtype);
      printDesc("bNumEmbMIDIJack:\t",       pMG->bNumEmbMIDIJack);
      printDesc("BaAssocJackID:\t\t",       pMG->BaAssocJackID);
      break;
    }
    default:
      printUnknownDesc(p);
      break;
  }
}
#else
#define printUnknownDesc(p)                     ((void)0)
#define printDeviceDesc(pD)                     ((void)0)
#define printDeviceQualifierDesc(pD)            ((void)0)
#define printConfigDesc(pC)                     ((void)0)
#define printEndpointDesc(pE)                   ((void)0)
#define printInterfaceDesc(pI)                  ((void)0)
#define printHIDDesc(pH)                        ((void)0)
#define printAudioControlInterfaceDesc(p)       ((void)0)
#define printMIDIStreamingInterfaceDesc(p)      ((void)0)
#define printMIDIStreamingEndpointDesc(p)       ((void)0)
#endif

void printStringDescriptor(UsbDevice *pdev, uint8_t index)
{
  uint8_t sbuf[256];
  uint8_t rcode, len;

  if (index == 0) return;

  for (uint8_t i = 0; i < LANGID_SIZE; i++) {
    if (langid[i] == 0) return;

    rcode = Usb.getStrDescr(pdev->address.devAddress, 0, 1, index, langid[i], sbuf);
    if (rcode) { printError(rcode); return; }
    len = (sbuf[0] > sizeof(sbuf) ? sizeof(sbuf) : sbuf[0]);

    rcode = Usb.getStrDescr(pdev->address.devAddress, 0, len, index, langid[i], sbuf);
    if (rcode) { printError(rcode); return; }

    xprint("String"); Serial.print(index);
    xprint("("); printHEX(langid[i]); xprint("): ");
    printVal("len", len);

    dumpBuf(sbuf[0], sbuf, true);

    // Print string
    xprint("// ");
    for (uint8_t j = 2; (j + 1) < len; j += 2) {
      if (sbuf[j + 1] != 0) {
        Serial.write('.');
        Serial.write('.');
        continue;
      } else {
        if (0x1F < sbuf[j] && sbuf[j] < 0x7F) {
          Serial.write(sbuf[j]);
        } else {
          Serial.write('.');
        }
        if (langid[i] != 0x0409) {
          Serial.write('.');
        }
      }
    }
    Serial.println();
  }
}

uint8_t parseReportDesc(UsbDevice *pdev, uint16_t iface, uint8_t index, uint16_t len, USBReadParser* parser)
{
  uint8_t rbuf[64];
  uint8_t rcode = 0;
  rcode = Usb.ctrlReq(pdev->address.devAddress, 0x00, bmREQ_HID_REPORT, USB_REQUEST_GET_DESCRIPTOR, index,
                      HID_DESCRIPTOR_REPORT, iface, len, sizeof(rbuf), rbuf, parser);
  Serial.println();
  if (rcode) { printError(rcode); }
  return rcode;
}

void scanConfigDesc(UsbDevice *pdev, uint16_t tl, uint8_t* pB)
{
  uint8_t iface = 0;
  uint8_t iClass = 0;
  uint8_t iSubClass = 0;
  uint8_t iProtocol = 0;
  while (pB < buf + tl) {
    switch (*(pB+1)) {
      case USB_DESCRIPTOR_CONFIGURATION:
        xprintln("\r\n// Config:");
        printConfigDesc((USB_CONFIGURATION_DESCRIPTOR *)pB);
        break;
      case USB_DESCRIPTOR_ENDPOINT:
        xprintln("\r\n// Endpoint:");
        printEndpointDesc((USB_ENDPOINT_DESCRIPTOR *)pB);
        break;
      case USB_DESCRIPTOR_INTERFACE: {
        USB_INTERFACE_DESCRIPTOR *pI = (USB_INTERFACE_DESCRIPTOR *)pB;
        iface = pI->bInterfaceNumber;
        iClass = pI->bInterfaceClass;
        iSubClass = pI->bInterfaceSubClass;
        iProtocol = pI->bInterfaceProtocol;

        xprint("\r\n// Interface"); Serial.print(iface);
        xprint("."); Serial.print(pI->bAlternateSetting); xprintln(":");
        printInterfaceDesc(pI);

        // String Descriptor
        if (pI->iInterface) {
          xprint("\r\n// iInterface: ");
          printStringDescriptor(pdev, pI->iInterface);
        }
        break;
      }

      case HID_DESCRIPTOR_HID: {
        USB_HID_DESCRIPTOR *pH = (USB_HID_DESCRIPTOR *)pB;

        xprintln("\r\n// HID: ");
        printHIDDesc(pH);

        // bDescrType and wDescriptorLength can be multiple
        uint8_t *p = pB + 6;
        for (int i = 0; i < pH->bNumDescriptors; i++) {
          uint8_t type = *(p + i * 3);
          uint16_t len = (uint16_t)(*(p + i * 3  + 1));

          if (type  == HID_DESCRIPTOR_REPORT) {
            xprint("\r\n// Report"); Serial.print(i); printVal(" dump:\tlen", len);
            parseReportDesc(pdev, iface, i, len, &dumper);

            #ifdef PRINT_DESC_REPORT
            xprint("\r\n// Report:");
            ReportDescParser report_parser;
            parseReportDesc(pdev, iface, i, len, &report_parser);
            #endif
          } else {
            printVal("\r\n// Unknown HID Desc: type:", pH->bDescrType);
          }
        }
        break;
      }

      // Class-Specific
      case CS_INTERFACE:
        // https://www.usb.org/sites/default/files/midi10.pdf
        // https://www.usb.org/sites/default/files/USB%20MIDI%20v2_0.pdf
        if (iClass == CLASS_AUDIO && iSubClass == AUDIO_CONTROL && iProtocol == 0) {
          printAudioControlInterfaceDesc(pB);
        } else if (iClass == CLASS_AUDIO && iSubClass == AUDIO_MIDI_STREAMING && iProtocol == 0) {
          printMIDIStreamingInterfaceDesc(pB);
        } else {
          printUnknownDesc(pB);
        }
        break;
      case CS_ENDPOINT:
        if (iClass == CLASS_AUDIO && iSubClass == AUDIO_MIDI_STREAMING && iProtocol == 0) {
          printMIDIStreamingEndpointDesc(pB);
        } else {
          printUnknownDesc(pB);
        }
        break;

      // not occur
      // case USB_DESCRIPTOR_CONFIGURATION:
      // case USB_DESCRIPTOR_STRING:
      case USB_DESCRIPTOR_DEBUG:
      case USB_DESCRIPTOR_INTERFACE_ASSOCIATION:
      case USB_DESCRIPTOR_BOS:
      case USB_DESCRIPTOR_DEVICE_CAPABILITY:
      case USB_DESCRIPTOR_SS_USB_EP_COMPANION:
      case USB_DESCRIPTOR_SSP_ISO_EP_COMPANION:
      default:
        printUnknownDesc(pB);
        break;
    }
    pB += *pB;
  }
}

uint8_t dumpConfigDesc(UsbDevice *pdev, uint8_t numConf)
{
  uint8_t rcode = 0;
  for (uint8_t i = 0; i < numConf; i++) {
    xprint("\r\n// Config"); Serial.print(i); xprint(" dump:\t");

    rcode = Usb.getConfDescr(pdev->address.devAddress, 0, sizeof(USB_CONFIGURATION_DESCRIPTOR), i, buf);
    if (rcode) return rcode;
    USB_CONFIGURATION_DESCRIPTOR *pC = (USB_CONFIGURATION_DESCRIPTOR *)&buf;
    printVal("len", pC->wTotalLength);

    uint16_t conf_len = (pC->wTotalLength < BUF_SIZE ? pC->wTotalLength : BUF_SIZE);
    rcode = Usb.getConfDescr(pdev->address.devAddress, 0, conf_len, i, buf);
    if (rcode) return rcode;
    dumpBuf(conf_len, buf);
    if (pC->wTotalLength > BUF_SIZE) xprintln("Buffer is not enough!");

    // String Descriptor
    if (pC->iConfiguration) {
      xprint("\r\n// iConfiguration: ");
      printStringDescriptor(pdev, pC->iConfiguration);
    }

    // Set Configuration
    // Without this some device STALL when getting Report Descriptor(ex. Wacom Intuos S)
    Usb.setConf(pdev->address.devAddress, 0, pC->bConfigurationValue);

    scanConfigDesc(pdev, conf_len, buf);
  }
  return rcode;
}

void dumpDescriptors(UsbDevice *pdev)
{
  USB_DEVICE_DESCRIPTOR *pD;
  uint8_t dClass = 0;
  uint8_t dSubClass = 0;
  uint8_t dProtocol = 0;
  uint8_t numConf = 0;
  uint8_t rcode = 0;

  for (int i = 0; i < LANGID_SIZE; i++) {
    langid[i] = 0;
  }

  // Hub is already intialized by driver and accessing its descriptor will cause problem
  if (pdev->address.devAddress & 0x40) {
    xprintln("\r\n// Hub: To dump descriptor of hub see NOTE in code");
    return;
  }

  Serial.println();
  for (int i = 0; i < 70; i++) Serial.write('/');
  xprintln("\r\n// USB_desc_dump");

  printValC("Address", pdev->address.devAddress);
  printValC("Lowspeed", (uint8_t)pdev->lowspeed);

  //
  // Device Descriptor
  //
  rcode = Usb.getDevDescr(pdev->address.devAddress, 0, sizeof(USB_DEVICE_DESCRIPTOR), buf);
  if (rcode) { printError(rcode); goto DONE; }
  pD = (USB_DEVICE_DESCRIPTOR *)&buf;

  dClass = pD->bDeviceClass;
  dSubClass = pD->bDeviceSubClass;
  dProtocol = pD->bDeviceProtocol;
  numConf = pD->bNumConfigurations;

  // set maxpacketsize0
  epInfo[0].epAddr = 0;
  epInfo[0].maxPktSize = pD->bMaxPacketSize0;
  epInfo[0].bmNakPower = USB_NAK_MAX_POWER;
  epInfo[0].bmSndToggle = 0;
  epInfo[0].bmRcvToggle = 0;
  Usb.GetAddressPool().GetUsbDevicePtr(pdev->address.devAddress)->epinfo = epInfo;

  xprintln("\r\n// Devicer dump:");
  dumpBuf(sizeof(USB_DEVICE_DESCRIPTOR), buf);

  xprintln("\r\n// Device:");
  printDeviceDesc(pD);

  //
  // String Descriptor
  //
  if (pD->iManufacturer || pD->iProduct || pD->iSerialNumber) {
    uint8_t sbuf[2 + LANGID_SIZE * 2];
    rcode = Usb.getStrDescr(pdev->address.devAddress, 0, 4, 0, 0, sbuf);
    if (rcode) { printError(rcode); goto STRING_DONE; }

    uint8_t len = (sbuf[0] > sizeof(sbuf) ? sizeof(sbuf) : sbuf[0]);
    rcode = Usb.getStrDescr(pdev->address.devAddress, 0, len, 0, 0, sbuf);
    if (rcode) { printError(rcode); goto STRING_DONE; }

    xprint("\r\n// String Zero: "); printVal("len", len);
    dumpBuf(sbuf[0], sbuf, true);

    xprint("// LangId: ");
    for (int i = 0; i < (len - 2) / 2; i++) {
      if (i > 0) xprint(", ");
      langid[i] = (sbuf[2 + i * 2 + 1] << 8) | sbuf[2 + i * 2];
      printHEX(langid[i]);
    }
    xprintln();
  }
  if (pD->iManufacturer) {
    xprint("\r\n// iManufacturer: ");
    printStringDescriptor(pdev, pD->iManufacturer);
  }
  if (pD->iProduct) {
    xprint("\r\n// iProduct: ");
    printStringDescriptor(pdev, pD->iProduct);
  }
  if (pD->iSerialNumber) {
    xprint("\r\n// iSerialNumber: ");
    printStringDescriptor(pdev, pD->iSerialNumber);
  }
STRING_DONE:

#ifdef PRINT_DESC_HSHUB
  // Hispeed Hub
  if (pD->bDeviceClass == CLASS_HUB && !pdev->lowspeed) {
    rcode = Usb.ctrlReq(pdev->address.devAddress, 0, bmREQ_GET_DESCR, USB_REQUEST_GET_DESCRIPTOR,
                        0, USB_DESCRIPTOR_DEVICE_QUALIFIER, 0, 10, 10, buf, NULL);
    if (rcode) { goto QUALIFILER_DONE; }
    xprintln("\r\n// Device Qualifier dump: ");
    dumpBuf(10, buf);

    xprintln("\r\n// Device Qualifier: ");
    USB_DEVICE_QUALIFIER_DESCRIPTOR *pDQ = (USB_DEVICE_QUALIFIER_DESCRIPTOR *)buf;
    printDeviceQualifierDesc(pDQ);

    uint8_t n = pDQ->bNumConfigurations;
    for (int i = 0; i < n; i++) {
      rcode = Usb.ctrlReq(pdev->address.devAddress, 0, bmREQ_GET_DESCR, USB_REQUEST_GET_DESCRIPTOR,
                          i, USB_DESCRIPTOR_OTHER_SPEED, 0, 9, 9, buf, NULL);
      if (rcode) { goto QUALIFILER_DONE; }
      xprintln("\r\n// Other Speed dump: ");
      dumpBuf(9, buf);
      xprintln("\r\n// Other Speed: ");
      printConfigDesc((USB_CONFIGURATION_DESCRIPTOR *)buf); // Other Speed is identical to Configuration
    }
  }
QUALIFILER_DONE:
#endif


  //
  // Configuration Descriptor
  //
  rcode = dumpConfigDesc(pdev, numConf);
  if (rcode) { printError(rcode); goto DONE; }

DONE:
  // Free address: devices are not released automatically without driver
  Usb.GetAddressPool().FreeAddress(pdev->address.devAddress);

  xprintln("\r\n// Parse data here: http://eleccelerator.com/usbdescreqparser/");
  return;
}

void setup()
{
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  while (!Serial);
#endif
  xprintln("Start");

  if (Usb.Init() == -1)
    xprintln("OSC did not start.");

  delay( 200 );
}

static uint8_t prev_state = 0;
static const uint8_t numdevices = (USB_NUMDEVICES > 16 ? 16 : USB_NUMDEVICES);
static uint16_t device_state = 0;

void loop()
{
  Usb.Task();

  // USB state
  if (prev_state != Usb.getUsbTaskState()) {
    prev_state = Usb.getUsbTaskState();
    printVal("usb_state", Usb.getUsbTaskState());
  }

  if (Usb.getUsbTaskState() == USB_STATE_RUNNING) {
    // Track device change
    UsbDevice *pool = Usb.GetAddressPool().GetUsbDevicePtr(0);
    for (int i = 0; i < numdevices; i++) {
      uint16_t s = ((pool[i].address.devAddress != 0) ? 1 : 0) << i;
      if ((device_state & (1 << i)) ^ s) {
        if (s) {
          // new device
          dumpDescriptors(pool + i);
        } else {
          // del device
        }
        device_state &= ~(1<<i);
        device_state |=  s;
      }
    }
  }
}

// vim: tabstop=2 softtabstop=2 shiftwidth=2 expandtab
