# Cold-Storage-Monitring-and-Management-System
# IoT based cold storage monitoring and management system
### What and for whom 
This project helps  a cold storage owner to monitor all the vital parameters(just say coolant temperature,vegetable temperature,humidity,door closed/open,secuirity breach) of any specific chamber through a website.

This website also helps the farmers who want to avail the service of cold storage, as they can make request to cold storage owner about the quantity and type of item they want to store and get the customized quotation from the owner. 

### Technologies used
 i) Internet of Things

 ii)HTML , CSS & JavaScript

 iii) Firebase




## Contents
 i) Components

 ii) Working

 iii) Features

### Components
 a) ESP32- It processes all incoming data from different  sensors.

 b)DHT11- This sensor measures the temperature and humidity.

 c)LM35- This sensor also measures temperature.

 d)PIR(motion sensor)- This sensor  is used to detect any motion.

 e)IR sensor- This sensor is used to detect door movement.

 f)Firebase- This is online database which recieves and stores data sent from ESP32.
 
 e)Website- Webpages are designed and linked together to show different data from firebase database in an interactive way.

### Working
DHT and LM35 measure the temperatures  and humidity between coolant and vegetable and compare them for checking the preservative mode.

ESP32 connected with internet  send real time temperature , humidity, preservative mode and security status to firebase.

Device also contain IR sensor , PIR sensor which are able to detect human motion in chamber and status of door .

Device also send the security alert or update on owner whatsapp.

Website contains homepage showing details of various services provided by the cold-storage enterprise and a link to  get authenticated as owner and move to owner's page.

Owner's page shows chamberwise data of different parameters.

Homepage contains another link too to sign up as user and request to cold storage owner for quotation of the type of item they want to store.
