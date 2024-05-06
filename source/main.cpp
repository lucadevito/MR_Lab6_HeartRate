/*----------------------------------------------------------------------------
LAB EXERCISE - BLE device
 ----------------------------------------
	In this exercise we will create a simple BLE device providing simulated heart rate measurements.
    We will use the Nucleo BLE shield (X-NUCLEO-IDB05A1).
    The system will be detectable from a cell phone and will allow to activate notifications for
    receiving the heart rate measurements.
    We can connect using the nRFConnect App from the smartphone.


	GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include <events/mbed_events.h>
#include <mbed.h>
#include "ble/BLE.h"
#include "ble/gap/Gap.h"
#include "ble/services/HeartRateService.h"
#include "ble/services/BatteryService.h"
#include "ble/services/DeviceInformationService.h"
#include "pretty_printer.h"

/** VARIABLE DEFINITIONS **/

/* device name */
const static char DEVICE_NAME[] = "Heartrate";

/* list of services */
UUID uuid_list[] = {
    /* Add service UUIDS:
        - Heart rate,
        - Battery,
        - Device Information */
    /* COMPLETE HERE */
        
    /****************/
    };

/* Advertising data buffer */
uint8_t adv_buffer[ble::LEGACY_ADVERTISING_MAX_SIZE];

/* BLE event queue */
static events::EventQueue event_queue(/* event count */ 16 * EVENTS_EVENT_SIZE);

/* flags */
/* DEFINE FLAGS */
/* COMPLETE HERE */

/****************/

/* Tickers: one for led blinking, another for measurement update */ 
/* DECLARE TICKERS */
/* COMPLETE HERE */

/****************/


/* LED object (LED1) */
/* DEFINE LED OBJECT */
/* COMPLETE HERE */

/****************/


/** HANDLERS **/

/* Handler for led Ticker */
/* WRITE CALLBACK FOR LED TICKER */
/* COMPLETE HERE */

/****************/

/* Handler for measurement update Ticker */
/* WRITE CALLBACK FOR MEASUREMENT UPDATE */
/* COMPLETE HERE */

/****************/

/** Callback triggered when the ble initialization process has finished */
void on_init_complete(BLE::InitializationCompleteCallbackContext *params) {
    if (params->error != BLE_ERROR_NONE) {
        printf("Ble initialization failed.");
        return;
    }
    
    /* UPDATE INIT COMPLETE FLAG */
    /* COMPLETE HERE */

    /****************/

}

/* class implementing EventHandler */
class HeartrateApp : ble::Gap::EventHandler {
public:
    HeartrateApp(BLE &ble, events::EventQueue &event_queue) :
        _ble(ble),
        _event_queue(event_queue),
        /* Add other initializers to the list:
           - private flag for connection state to false
           - heart rate value to 100 (bpm)
           - battery level to 100 (%)
           - Heart rate service with proper constructor
           - Battery service with proper constructor
           - Device information service with proper constructor */
        /* COMPLETE HERE */

        /****************/
        {}
    
    void update_sensor_value() {
        if (_connected) {
            /* Update Heart Rate measurement (by simulation)
               the value should be increased by 1 every second 
               until it reaches 175, then shold drop to 100 and 
               restart counting.
               At the end, update value to the BLE Heart rate service */
            /* COMPLETE HERE */

            /****************/
        }
    }

private:
    /* Event handler */

    void onDisconnectionComplete(const ble::DisconnectionCompleteEvent&) {
        /* Start advertising */
        /* COMPLETE HERE */

        /****************/
        
        /* Update the private flag of connection state to false */
        /* COMPLETE HERE */

        /****************/
    }

    void onConnectionComplete(const ble::ConnectionCompleteEvent &event) {
        if (event.getStatus() == BLE_ERROR_NONE) {
            /* Update the private flag of connection state to true */
            /* COMPLETE HERE */

            /****************/
        }
    }

private:
    BLE &_ble;
    events::EventQueue &_event_queue;

    /* define private connection state flag */
    /* COMPLETE HERE */

    /****************/

    /* define heart rate counter variable */
    /* COMPLETE HERE */

    /****************/

    /* define batery level variable */
    /* COMPLETE HERE */

    /****************/
    
    /* define Services members (HeartRateService, BatteryService, DeviceInformationService) */
    /* COMPLETE HERE */

    /****************/
};

/** Schedule processing of events from the BLE middleware in the event queue. */
void schedule_ble_events(BLE::OnEventsToProcessCallbackContext *context) {
    event_queue.call(Callback<void()>(&context->ble, &BLE::processEvents));
}

void start_advertising(BLE &ble) {

    /* Create AdvertisingDataBuilder object */
    /* COMPLETE HERE */

    /****************/

    /* define AdvertisingParameters object
       with advertising interval to 1 s */
    /* COMPLETE HERE */

    /****************/

    /* Fill in advertising data 
      - set Flags (Default) 
      - set Appearance
      - set device name
      - set service list */
    /* COMPLETE HERE */

    /****************/
    
    /* Set advertising parameters*/
    ble_error_t error = ble.gap().setAdvertisingParameters(
        ble::LEGACY_ADVERTISING_HANDLE,
        adv_parameters
    );

    if (error) {
        printf("_ble.gap().setAdvertisingParameters() failed\r\n");
        return;
    }

    /* set Advertising payload */
    error = ble.gap().setAdvertisingPayload(
        ble::LEGACY_ADVERTISING_HANDLE,
        adv_data_builder.getAdvertisingData()
    );

    if (error) {
        printf("_ble.gap().setAdvertisingPayload() failed\r\n");
        return;
    }

    /* Start advertising */
    error = ble.gap().startAdvertising(ble::LEGACY_ADVERTISING_HANDLE);

    if (error) {
        printf("_ble.gap().startAdvertising() failed\r\n");
        return;
    }
}

int main()
{
    /* Access BLE Device instance */
    /* COMPLETE HERE */

    /****************/

    /* set Callback for BLE stack events */
    ble.onEventsToProcess(schedule_ble_events);

    /* Define EventHandler and attach it to the BLE Device*/
    /* COMPLETE HERE */

    /****************/

    /* Init BLE Device */
    /* COMPLETE HERE */

    /****************/
  
    /* Main loop */
    while (1) {
        /* check flag and take actions */
        /* - init complete
        /* COMPLETE HERE */
        
        /****************/
        {

            print_mac_address();
     
            start_advertising(ble);

            /* attach callbacks to Tickers */
            /* COMPLETE HERE */
        
            /****************/
        }
        /* - led flag */
        /* COMPLETE HERE */
        
        /****************/

        /* - measurement update flag */
        /* COMPLETE HERE */
        
        /****************/

        /* check for BLE events */
        event_queue.dispatch(100);
    }
    return 0;
}

