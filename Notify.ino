#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBold9pt7b.h> //

// --- إعدادات الواي فاي الخاصة بك --- KEEP Quotation Marks, Just Add Your WIFI Information
const char* ssid = "YOUR WIFI"; 
const char* password = "YOUR PASSWORD";
WebServer server(80);
Adafruit_SSD1306 display(128, 64, &Wire, -1);
const int buzzerPin = 4;

// العداد الداخلي اللي يصفر عند 5
int internalCounter = 0; 

void handleNotification() {
  // زيادة العداد الداخلي في كل مرة يصل إشعار
  internalCounter++;

  // 1. تنبيه البازر (نغزة سريعة)
  // النغمة الأولى
  digitalWrite(buzzerPin, HIGH); 
  delay(100); 
  digitalWrite(buzzerPin, LOW);

  // صمت بين النغمتين (ضروري جداً)
  delay(80); 

  // النغمة الثانية
  digitalWrite(buzzerPin, HIGH); 
  delay(100); 
  digitalWrite(buzzerPin, LOW);
  
  display.clearDisplay();
  display.setTextColor(WHITE);

  // 2. سطر Whatsapp (الحجم المتوسط الاحترافي)
  // استخدمنا خط FreeSansBold12pt7b عشان يكون أصغر من 2 وأكبر من 1
  display.setFont(&FreeSansBold9pt7b); 
  display.setCursor(0, 30);            
  display.println("Whatsapp");

  // 3. سطر عدد الرسائل (الخط العادي الحجم 1)
  display.setFont();                   // العودة للخط الافتراضي
  display.setTextSize(1);              // تقدر تعدل الرقم هنا بكيفك (مثلاً 2)
  display.setCursor(0, 50);            
  display.print("Message(s) : ");
  display.print(internalCounter);      // عرض العداد الداخلي

  display.display();

  // 4. تصفير العداد إذا وصل 5
  if (internalCounter >= 5) {
    internalCounter = 0; 
  }
  
  server.send(200, "text/plain", "OK");
  
  // الشاشة تطفي بعد 7 ثواني (Stealth Mode)
  delay(7000); 
  display.clearDisplay();
  display.display();
}

void setup() {
  setCpuFrequencyMhz(80);
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;);
  }
  
  display.clearDisplay();
  display.display(); // تبدأ الشاشة سوداء

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/notify", handleNotification); 
  server.begin();
}

void loop() {
  server.handleClient(); 
}
