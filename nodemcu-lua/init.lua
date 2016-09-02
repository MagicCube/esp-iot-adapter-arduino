uart.setup(0, 9600, 8, uart.PARITY_NONE, uart.STOPBITS_1, 1)

data = {}

function connectToAP(ssid, password)
    wifi.setmode(wifi.STATION)
    wifi.sta.config(ssid, password, 1)
end

function startAP(ssid, password)
    wifi.setmode(wifi.STATIONAP)
    if password == nil or password == "" then
        wifi.ap.config({
            ssid = ssid,
            auth = wifi.OPEN
        })
    else
        wifi.ap.config({
            ssid = ssid,
            pwd = password
        })
    end
end

function setData(key, value)
    data[key] = value;
end

function startServer()
    server = net.createServer(net.TCP)
    server:listen(80, function(conn)
        conn:on("receive", function(socket, payload)
            socket:send("HTTP/1.0 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n" .. cjson.encode(data))
        end)
        conn:on("sent", function(socket) socket:close() end)
    end)
end
