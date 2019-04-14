# MWIT_Project
![alt_text](https://img.shields.io/badge/Compatible-ArduinoIDE-green.svg "bulidpassing")
![alt_text](https://img.shields.io/badge/Support-ESP8266-blue.svg "bulidpassing")<br>
Project กลุ่ม ของสาขาคอมพิวเตอร์ จากการอบรม Easy loT Education by Blynk 
โดยครูจากโรงเรียนพิจิตรพิทยาคม และโรงเรียนนครนายกวิทยาคม
![alt_text](https://sv1.picz.in.th/images/2019/04/14/tFsnO9.jpg)
ในวันที่ 26-29 มีนาคม 2561 อบรมเชิงปฏิบัติการ ปี 2561 ตามโครงการพัฒนาความรู้ทางวิชาการด้านคณิตศาสตร์ และวิทยาศาสตร์ สำหรับครูระดับมัธยมศึกษาตอนปลาย รุ่นที่ 4-5 (ครั้งที่ 4 สำหรับรุ่นที่ 5) ณ โรงเรียนมหิดลวิทยานุสรณ์

![alt_text](https://sv1.picz.in.th/images/2019/04/14/tFsHzb.jpg)
หลักการทำงาน
1. นำค่าความชื้่น, อุณหภูมิในอากาศ และความเข้มแสง เข้า OLED ของ AX-WiFi และ Blynk App 
2. ถ้าค่าความเข้มแสงที่ได้รับ ณ ขณะนั้น มีค่าน้อยกว่า ค่าใน Slider ใน Blynk App จะทำให้
  2.1 ZX-LED บอร์ดขับ LED 8 มม.สีเขียว สถานะไฟติด
  2.2 ZX-LED บอร์ดขับ LED 8 มม.สีแดง สถานะไฟดับ
  2.3 Relay Module 1 Channel สถานะ Active High Level (ทำงาน) ส่งผลให้หลอดไฟติด
  2.4 Line Notify แจ้งข้อความ "LED Turn on : "
3. ถ้าค่าความเข้มแสงที่ได้รับ ณ ขณะนั้น มีค่ามากกว่าหรือเท่ากับ ค่าใน Slider ใน Blynk App จะทำให้
  3.1 ZX-LED บอร์ดขับ LED 8 มม.สีเขียว สถานะไฟดับ
  3.2 ZX-LED บอร์ดขับ LED 8 มม.สีแดง สถานะไฟติด
  3.3 Relay Module 1 Channel สถานะ Active Low Level (ไม่ทำงาน) ส่งผลให้หลอดไฟดับ
  3.4 Line Notify แจ้งข้อความ "LED Turn off : "

รายการอุปกรณ์
- https://inex.co.th/shop/education-board/iot/iot-activity-kit-blynk-version.html
![รายการของ activity-kit-blynk-version](https://sv1.picz.in.th/images/2019/04/14/tFs6kD.jpg)
- หาเพิ่มเติม คือ Relay Module 1 Channel (Active high Level), สายไฟ,ปลั๊กไฟ และหลอดไฟ การเชื่อมต่อนั้นดูได้จากรูป Relay.jpg ใน Project นี้ 
![alt_text](https://sv1.picz.in.th/images/2019/04/14/tFsyaZ.jpg)

การเชื่อมต่ออุปกรณ์ระหว่าง Sensor ต่างๆ กับ AX-WiFi
1. Relay Module 1 Channel(IN,VCC,GND) เชื่อมต่อกับ AX-WiFi (D0,VIN,GND)
2. ZX-BH1750 โมดูลตัวตรวจวัดความเข้มแสง(SCL,SDA,VCC,GND) เชื่อมต่อกับ AX-WiFi (D1,D2,3V3,GND)
3. ZX-AM2302 โมดูลตัวตรวจจับความชื้นสัมพัทธ์ และอุณหภูมิ เชื่อมต่อกับ AX-WiFi (D4,3V3,GND)
4. ZX-LED บอร์ดขับ LED 8 มม.สีเขียว เชื่อมต่อกับ AX-WiFi (D5)
5. ZX-LED บอร์ดขับ LED 8 มม.สีแดง เชื่อมต่อกับ AX-WiFi (D6)

การตั้งค่า Widget ใน Blynk App (สามารถดูในรูป Picture4.jpg-Picture10.jpg)
1. Guage ให้ตั้งค่าไปที่ V5 สำหรับแสดงค่าความชื้นในอากาศ
2. Guage ให้ตั้งค่าไปที่ V6 สำหรับแสดงค่าอุณหภูมิในอากาศ
3. Guage ให้ตั้งค่าไปที่ V1 สำหรับแสดงค่าความเข้มแสง
4. Slider ให้ตั้งค่าไปที่ V0 สำหรับส่งค่า ไปยัง AX-WiFi

Related Post :
- https://youtu.be/gpqesnBAggE (ตัวอย่างวิดีโอ)
- https://www.facebook.com/manoch.sangsiri/posts/2061539797449354 (การนำเสนอ Project ตอนอบรม)
- https://www.facebook.com/ManochICT/posts/1967380040246844

หากมีข้อสงสัย หรือ สอบถามสามารถแจ้งได้ที่ https://www.facebook.com/ManochICT , sangsiri@gmail.com ขอบคุณครับ
