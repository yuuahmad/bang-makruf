/**
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2021 mobizt
 *
*/

//This example shows how to list all files in Firebase and Google Cloud storage bucket via Google Cloud Storage JSON API.
//The Google Cloud Storage JSON API function required OAuth2.0 authen.

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "WIFI_AP"
#define WIFI_PASSWORD "WIFI_PASSWORD"

/* 2. Define the Firebase project host name (required) */
#define FIREBASE_HOST "PROJECT_ID.firebaseio.com"

/* 3. Define the Firebase storage bucket ID e.g bucket-name.appspot.com */
#define STORAGE_BUCKET_ID "BUCKET-NAME.appspot.com"

/* 4 The following Service Account credentials required for OAuth2.0 authen in Google Cloud Storage JSON API list files */
#define FIREBASE_PROJECT_ID "PROJECT_ID"
#define FIREBASE_CLIENT_EMAIL "CLIENT_EMAIL"
const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY-----XXXXXXXXXXXX-----END PRIVATE KEY-----\n";

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

String path = "/Test";

void setup()
{

    Serial.begin(115200);
    Serial.println();
    Serial.println();

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    /* Assign the project host (required) */
    config.host = FIREBASE_HOST;

    /* Assign the Service Account credentials for OAuth2.0 authen */
    config.service_account.data.client_email = FIREBASE_CLIENT_EMAIL;
    config.service_account.data.project_id = FIREBASE_PROJECT_ID;
    config.service_account.data.private_key = PRIVATE_KEY;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

#if defined(ESP8266)
    //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
    fbdo.setBSSLBufferSize(1024, 1024);
#endif


    Serial.println("------------------------------------");
    Serial.println("List files with Google Cloud Storage JSON API test...");

    //Fore query parameters description of ListOptions, see https://cloud.google.com/storage/docs/json_api/v1/objects/list#optional-parameters
    ListOptions option;
    option.maxResults = "10";

    if (Firebase.GCStorage.listFiles(&fbdo, STORAGE_BUCKET_ID /* The Firebase or Google Cloud Storage bucket id */, &option /* ListOptions data */))
    {
        Serial.println("PASSED");
        FileList *files = fbdo.fileList();
        for (size_t i = 0; i < files->items.size(); i++)
            Serial.printf("name: %s, bucket: %s, contentType: %s, size: %d\n", files->items[i].name.c_str(), files->items[i].bucket.c_str(), files->items[i].contentType.c_str(), files->items[i].size);
        Serial.println("------------------------------------");
        Serial.println();
    }
    else
    {
        Serial.println("FAILED");
        Serial.println("REASON: " + fbdo.errorReason());
        Serial.println("------------------------------------");
        Serial.println();
    }

}

void loop()
{
}
