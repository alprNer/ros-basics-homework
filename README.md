# 🚀 ROS1 NOETIC ÖDEV 1 VE 2

**Hazırlayan:** Muhammet Alperen ER

Bu dokümantasyon, ROS1 Noetic üzerinde C++ kullanılarak geliştirilmiş iki farklı haberleşme (Service/Client ve Publisher/Subscriber) uygulamasının dosya yapılarını, derleme ayarlarını ve çalıştırma adımlarını içermektedir.

---

## 🧮 ÖDEV 1: Özel Servis ile Dikdörtgen Alanı Hesaplama
**Paket Adı:** `pkg1_package`

Bu uygulamada, kullanıcının girdiği "en" ve "boy" değerlerini alarak dikdörtgenin alanını hesaplayan bir ROS servisi oluşturulmuştur. Olası sensör veya kullanıcı hatalarına karşı sistemin çökmesini engellemek amacıyla negatif değer girişleri filtrelenmiştir.

### 📁 1. Dosya Yapısı ve Oluşturma
Kendi paketimiz olan `pkg1_package` içerisinde geliştirmeler yapılmıştır:
* **Servis Mesajı:** Paketin ana dizininde `srv` klasörü açılarak içine `d_alan.srv` dosyası oluşturulmuştur.
* **Kaynak Kodlar:** Paketin `src` klasörü içerisine sunucu düğümü için `alan_server.cpp` ve istemci düğümü için `alan_client.cpp` dosyaları oluşturulmuştur.

### ⚙️ 2. CMakeLists.txt ve package.xml Ayarları
* `package.xml` dosyasına `message_generation` ve `message_runtime` bağımlılıkları eklenmiştir.
* `CMakeLists.txt` dosyasında sırasıyla:
  * `find_package` içerisine `message_generation` eklenmiştir.
  * `add_service_files` bölümü aktif edilerek `d_alan.srv` tanıtılmıştır.
  * C++ kodlarının derlenmesi için `add_executable` kuralları eklenmiş, servis dosyalarının önceden derlenmesi için `add_dependencies` tanımlanmış ve kütüphaneler `target_link_libraries` ile bağlanmıştır.

### 💻 3. Çalıştırma Adımları
Sistemi ayağa kaldırmak için 3 farklı terminal sekmesi kullanılmalıdır. Her terminalde öncelikle çalışma alanının yolu sisteme tanıtılmalıdır (`source devel/setup.bash`).

**Adım 1: ROS Master'ı Başlatın**
```bash
roscore
```

**Adım 2: Sunucuyu (Server) Başlatın**
```bash
rosrun pkg1_package alan_server
```
*(Ekranda "Alan hesaplama sunucusu calisiyor..." mesajı görülmeli ve sistem beklemeye geçmelidir.)*

**Adım 3: İstemciyi (Client) Çalıştırın ve İstek Gönderin**
```bash
rosrun pkg1_package alan_client 5.5 4.0
```
*(Bu komut sonrasında istemci terminalinde sonuç yazdırılırken, sunucu terminalinde gelen log kayıtları görüntülenecektir. Negatif değer girildiğinde sistem hata uyarısı verir.)*

---

## 🐢 ÖDEV 2: Turtlesim Otonom Hareket ve Konum Takibi
**Paket Adı:** `turtle_odevi`

Bu uygulamada otonom hareket eden bir robotun konum takibini sağlamak için bir örnek uygulama yapılmıştır. Bir düğüm `/turtle1/cmd_vel` topiğine sürekli hareket komutları (Publisher) gönderirken, eşzamanlı olarak çalışan diğer bir düğüm `/turtle1/pose` topiğini dinleyerek (Subscriber) robotun anlık konumunu takip eder.


### 📁 1. Dosya Yapısı ve Oluşturma
Bu ödev için bağımsız ve düzenli çalışması adına `turtle_odevi` adında yeni bir paket oluşturulmuştur.
* **Kaynak Kodlar:** Paketin `src` klasörü içerisine robotu hareket ettiren kod için `turtle_publisher.cpp` ve konumu okuyan kod için `turtle_listener.cpp` dosyaları oluşturulmuştur.

### ⚙️ 2. CMakeLists.txt Ayarları
Paketin C++ düğümlerini derleyip çalıştırılabilir (executable) programlara dönüştürebilmesi için `CMakeLists.txt` dosyasının en altına şu kurallar eklenmiştir:

* `add_executable(turtle_publisher src/turtle_publisher.cpp)`: Yayıncı kodunu derleyerek 'turtle_publisher' adında çalıştırılabilir bir düğüm oluşturur.
* `add_executable(turtle_listener src/turtle_listener.cpp)`: Dinleyici kodunu derleyerek 'turtle_listener' adında çalıştırılabilir bir düğüm oluşturur.
* `target_link_libraries(turtle_publisher ${catkin_LIBRARIES})` ve `target_link_libraries(turtle_listener ${catkin_LIBRARIES})`: Derlenen bu her iki düğümün de ROS'un temel kütüphaneleriyle bağlantı kurmasını (linklenmesini) sağlayarak ROS fonksiyonlarının çalışmasını garanti altına alır.

### 💻 3. Çalıştırma Adımları
Sistemi tam zamanlı test etmek için 4 farklı terminal sekmesi kullanılmalıdır. Her terminalde öncelikle çalışma alanı kaynaklanmalıdır (`source devel/setup.bash`).

**Adım 1: ROS Master'ı Başlatın**
```bash
roscore
```

**Adım 2: Turtlesim Simülasyonunu Başlatın**
```bash
rosrun turtlesim turtlesim_node
```

**Adım 3: Robotu Hareket Ettiren Yayıncıyı (Publisher) Başlatın**
```bash
rosrun turtle_odevi turtle_publisher
```
*(Bu komut çalıştırıldığında simülasyondaki kaplumbağa çember çizerek hareket etmeye başlayacaktır.)*

**Adım 4: Konumu Takip Eden Dinleyiciyi (Subscriber) Başlatın**
```bash
rosrun turtle_odevi turtle_listener
```
*(Bu komut çalıştırıldığında, kaplumbağanın anlık X, Y ve Açı değerleri terminal ekranına sürekli güncellenerek yazdırılacaktır.)*