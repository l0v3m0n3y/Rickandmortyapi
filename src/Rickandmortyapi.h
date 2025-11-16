#ifndef RICKANDMORTYAPI_H
#define RICKANDMORTYAPI_H

#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <pplx/pplx.h>
#include <iostream>
#include <string>
#include <map>

using namespace web;
using namespace web::http;
using namespace web::http::client;

class Rickandmortyapi {
private:
    std::string api_base = "https://rickandmortyapi.com/api";
    http_client_config client_config;
    
    http_request create_request(const std::string& path, method m, const std::string& body_data = "", const std::string& content_type = "") {
        http_request request(m);
        
        // Полный набор браузерных заголовков
        request.headers().add("Accept", "application/json");
        request.headers().add("Content-Type", "application/json"); 
        request.headers().add("User-Agent", "Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/115.0");
        
        // Устанавливаем тело запроса, если передано
        if (!body_data.empty() && !content_type.empty()) {
            request.set_body(body_data, utility::conversions::to_string_t(content_type));
        }
        
        request.set_request_uri(utility::conversions::to_string_t(path));
        return request;
    }

    std::string build_query_params(const std::map<std::string, std::string>& params) {
        if (params.empty()) return "";
        
        std::string query = "?";
        bool first = true;
        for (const auto& param : params) {
            if (!param.second.empty()) {
                if (!first) query += "&";
                query += param.first + "=" + param.second;
                first = false;
            }
        }
        return query;
    }

public:
    Rickandmortyapi() {
        client_config.set_validate_certificates(false);
    }

    pplx::task<json::value> get_episode_list(int page=1) {
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::map<std::string, std::string> params;
        bool first_param = true;
        if (page!=0) params["page"] = std::to_string(page);
        std::string path = "/episode";
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_episode(int episode_id=0,const std::string& name="",const std::string& air_date="",const std::string& episode="",const std::string& created="") {
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        uri_builder builder;
        if (episode_id != 0) {builder.set_path(U("/episode/" + std::to_string(episode_id)));
        } else {
        // Search episodes with query parameters
        builder.set_path(U("/episode/"));
        
        // Add query parameters
        if (!name.empty()) {
            builder.append_query(U("name"), utility::conversions::to_string_t(name));
        }
        if (!air_date.empty()) {
            builder.append_query(U("air_date"), utility::conversions::to_string_t(air_date));
        }
        if (!episode.empty()) {
            builder.append_query(U("episode"), utility::conversions::to_string_t(episode));
        }
        if (!created.empty()) {
            builder.append_query(U("created"), utility::conversions::to_string_t(created));
        }
    }
        auto request = create_request(builder.to_string(), methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_location_list(int page=1) {
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::map<std::string, std::string> params;
        bool first_param = true;
        if (page!=0) params["page"] = std::to_string(page);
        std::string path = "/location";
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_location(int location_id=0,const std::string& name="",const std::string& type="",const std::string& dimension="",const std::string& created="") {
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        uri_builder builder;
        if (location_id != 0) {builder.set_path(U("/location/" + std::to_string(location_id)));
        } else {
        // Search episodes with query parameters
        builder.set_path(U("/location/"));
        
        // Add query parameters
        if (!name.empty()) {
            builder.append_query(U("name"), utility::conversions::to_string_t(name));
        }
        if (!type.empty()) {
            builder.append_query(U("type"), utility::conversions::to_string_t(type));
        }
        if (!dimension.empty()) {
            builder.append_query(U("dimension"), utility::conversions::to_string_t(dimension));
        }
        if (!created.empty()) {
            builder.append_query(U("created"), utility::conversions::to_string_t(created));
        }
    }
        auto request = create_request(builder.to_string(), methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_character_list(int page=1) {
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::map<std::string, std::string> params;
        bool first_param = true;
        if (page!=0) params["page"] = std::to_string(page);
        std::string path = "/character";
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> get_location(int character_id=0,const std::string& name="",const std::string& status="",const std::string& species="",const std::string& type="",const std::string& gender="",const std::string& origin="",const std::string& location="",const std::string& created="") {
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        uri_builder builder;
        if (character_id != 0) {builder.set_path(U("/character/" + std::to_string(character_id)));
        } else {
        // Search episodes with query parameters
        builder.set_path(U("/character/"));
        
        // Add query parameters
        if (!name.empty()) {
            builder.append_query(U("name"), utility::conversions::to_string_t(name));
        }
        if (!status.empty()) {
            builder.append_query(U("status"), utility::conversions::to_string_t(status));
        }
        if (!species.empty()) {
            builder.append_query(U("species"), utility::conversions::to_string_t(species));
        }
        if (!type.empty()) {
            builder.append_query(U("type"), utility::conversions::to_string_t(type));
        }
        if (!gender.empty()) {
            builder.append_query(U("gender"), utility::conversions::to_string_t(gender));
        }
        if (!origin.empty()) {
            builder.append_query(U("origin"), utility::conversions::to_string_t(origin));
        }
        if (!location.empty()) {
            builder.append_query(U("location"), utility::conversions::to_string_t(location));
        }
        if (!created.empty()) {
            builder.append_query(U("created"), utility::conversions::to_string_t(created));
        }
    }
        auto request = create_request(builder.to_string(), methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
};

#endif
