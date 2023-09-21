#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>


using json = nlohmann::json;


struct Aircraft {
    std::string icao24;// "AB1234"
    std::string callsign;// "XYZ123",
    std::string origin_country;// "United States",
    unsigned long time_position;// 1632044090,
    unsigned long last_contact;// 1632044100,
    double longitude;// -123.456789,
    double latitude;// 45.678901,
    double baro_altitude;//: 10000.0,
    std::string on_ground;//: false,
    double velocity;// 250.0,
    double true_track;// 45.0,
    double vertical_rate;// 100.0,
    // "sensors": [],
    double geometric_altitude;// 9500.0,
    std::string squawk;// "1234",
    std::string spi;// false,
    unsigned long position_source;// 0
};

// Callback-функция для обработки данных от сервера
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string api_url = "https://opensky-network.org/api/states/all";

    // Инициализация библиотеки libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Создание объекта CURL
    curl = curl_easy_init();

    if (curl) {
        // Установка URL-адреса для запроса
        curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());

        // Установка callback-функции для обработки данных от сервера
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Создание переменной для хранения ответа от сервера
        std::string response;

        // Установка переменной для хранения ответа
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Выполнение HTTP-запроса
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Обработка ответа от сервера (ваш код обработки данных)
            //std::cout << "Response from API: " << response << std::endl;
            json parsed_data = json::parse(response);
            std::vector<Aircraft> aircraft_data;
            
            for (const auto& aircraft : parsed_data["states"]) {
                std::cout << aircraft << std::endl;
                Aircraft current_aircraft;
                current_aircraft.icao24 = aircraft[0].get<std::string>();
                current_aircraft.callsign = aircraft[1].get<std::string>();
                current_aircraft.origin_country = aircraft[2].get<std::string>();
                if (!aircraft[3].is_null()) {
                current_aircraft.time_position = aircraft[3].get<unsigned long>();
            }
            // Проверяем, что поле "last_contact" не равно null
            if (!aircraft[4].is_null()) {
                current_aircraft.last_contact = aircraft[4].get<unsigned long>();
            }
            // Проверяем, что поле "longitude" не равно null
            if (!aircraft[5].is_null()) {
                current_aircraft.longitude = aircraft[5].get<double>();
            }
            // Проверяем, что поле "latitude" не равно null
            if (!aircraft[6].is_null()) {
                current_aircraft.latitude = aircraft[6].get<double>();
            }
            // Проверяем, что поле "baro_altitude" не равно null
            if (!aircraft[7].is_null()) {
                current_aircraft.baro_altitude = aircraft[7].get<double>();
            }
            // Проверяем, что поле "on_ground" не равно null
            if (!aircraft[8].is_null()) {
                current_aircraft.on_ground = aircraft[8].get<bool>();
            }
            // Проверяем, что поле "velocity" не равно null
            if (!aircraft[9].is_null()) {
                current_aircraft.velocity = aircraft[9].get<double>();
            }
            // Проверяем, что поле "true_track" не равно null
            if (!aircraft[10].is_null()) {
                current_aircraft.true_track = aircraft[10].get<double>();
            }
            // Проверяем, что поле "vertical_rate" не равно null
            if (!aircraft[11].is_null()) {
                current_aircraft.vertical_rate = aircraft[11].get<double>();
            }
            // Проверяем, что поле "sensors" не пустое
            //if (!aircraft[12].is_null()) {
            //    for (const auto& sensor : aircraft[12]) {
            //        std::string sensor_id = sensor.get<std::string>();
            //        current_aircraft.sensors.push_back(sensor_id);
            //    }
            //}
            // Проверяем, что поле "geometric_altitude" не равно null
            if (!aircraft[13].is_null()) {
                current_aircraft.geometric_altitude = aircraft[13].get<double>();
            }
            // Проверяем, что поле "squawk" не равно null
            if (!aircraft[14].is_null()) {
                current_aircraft.squawk = aircraft[14].is_string() ? aircraft[14].get<std::string>() : ""; // Обрабатываем как строку, если поле не числовое

            }
            // Проверяем, что поле "spi" не равно null
            if (!aircraft[15].is_null()) {
                current_aircraft.spi = aircraft[15].get<bool>();
            }
            // Проверяем, что поле "position_source" не равно null
            if (!aircraft[16].is_null()) {
                current_aircraft.position_source = aircraft[16].get<unsigned long>();
            }

                // Добавляем текущий самолет к вектору
                aircraft_data.push_back(current_aircraft);
            }
            // ...


            // Вывод данных о самолетах (пример)
            for (const auto& aircraft : aircraft_data) {
                std::cout << "ICAO24: " << aircraft.icao24 << std::endl;
                std::cout << "Callsign: " << aircraft.callsign << std::endl;
                std::cout << "Origin Country: " << aircraft.origin_country << std::endl;
                // Вывод остальных полей
                std::cout << std::endl;
            }

            //std::cout << obj["icao24"] << std::endl;
            /*
            std::string icao24;// "AB1234"
            std::string callsign;// "XYZ123",
            std::string origin_country;// "United States",
            unsigned long time_position;// 1632044090,
            unsigned long last_contact;// 1632044100,
            double longitude;// -123.456789,
            double latitude;// 45.678901,
            double baro_altitude;//: 10000.0,
            bool on_ground;//: false,
            double velocity;// 250.0,
            double true_track;// 45.0,
            double vertical_rate;// 100.0,
            // "sensors": [],
            double geometric_altitude;// 9500.0,
            unsigned long squawk;// "1234",
            bool spi;// false,
            unsigned long position_source;// 0
            */
            //std::cout << obj.dump(4) << std::endl;
        }

        // Освобождение ресурсов
        curl_easy_cleanup(curl);
    }

    // Освобождение глобальных ресурсов libcurl
    curl_global_cleanup();

    return 0;
}
