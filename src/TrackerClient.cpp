// Copyright (c) Raphael Prandini Thome de Abrantes 2023

#include "TrackerClient.h"
#include <boost/asio/io_context.hpp>
#include <boost/format.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast.hpp>
#include <boost/beast/core/flat_buffer.hpp>


BencodeObject TrackerClient::get_result(const std::string &tracker, const std::string &escaped_hash) const {
    // FIXME: naive implementation
    size_t separator_position = tracker.find("//");
    size_t port_postion = tracker.find(':', separator_position);
    size_t url_path_position = tracker.find('/', port_postion);

    std::string host_name = tracker.substr(separator_position+2, port_postion - (separator_position + 2));
    std::string port_req = tracker.substr(port_postion+1, url_path_position - (port_postion + 1));
    std::string path_req = tracker.substr(url_path_position + 1);
    boost::asio::io_context ioc;
    boost::format url =
            boost::format(m_request_format) % path_req % "pO9iEEJs5CQi7kyNFBEw" % escaped_hash % 6881 % 100 % 0 % 0 % "started";
    boost::asio::ip::tcp::resolver resolver(ioc);
    boost::beast::tcp_stream stream(ioc);

    auto const results = resolver.resolve(host_name, port_req);
    stream.connect(results);
    boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::get, url.str(), 11};
    req.target(url.str());
    req.set(boost::beast::http::field::user_agent,"Torrant/0.0.1");
    req.set(boost::beast::http::field::accept, "*/*");
    req.set(boost::beast::http::field::host, host_name + ":" + port_req);
    req.set(boost::beast::http::field::connection, "keep-alive");
    boost::beast::http::write(stream, req);
    boost::beast::flat_buffer net_buffer;
    boost::beast::http::response<boost::beast::http::string_body> res;
    boost::beast::http::read(stream, net_buffer, res);
    stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both);

    return BencodeObject::from_string(res.body());
}
