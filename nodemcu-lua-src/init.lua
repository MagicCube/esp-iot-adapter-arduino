-- Set baud rate to 9600 and switch off echo
uart.setup(0, 9600, 8, uart.PARITY_NONE, uart.STOPBITS_1, 0)

data = {}

function connectToAP(ssid, password)
    if password == nil then
        password = ""
    end
    wifi.setmode(wifi.STATION)
    wifi.sta.config(ssid, password, 1)
end

function configAP(ssid, password)
    wifi.setmode(wifi.SOFTAP)
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

function getData()
    return data;
end

function getDataString()
    return cjson.encode(data);
end

function setValue(key, value)
    data[key] = value;
end

function getValue(key, value)
    return data[key];
end

function startServer()
    server = net.createServer(net.TCP)
    server:listen(80, function(conn)
        conn:on("receive", function(socket, payload)
            socket:send("HTTP/1.0 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n" .. getDataString())
        end)
        conn:on("sent", function(socket) socket:close() end)
    end)
end
