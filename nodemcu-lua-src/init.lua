-- Set baud rate to 9600
-- WARNING:
-- By default, we switch off the echo in order to get pure result
-- If you want to use ESPlorer or other IDE upload lua script, you need to
-- manully use the following code to switch echo on first.
--
-- uart.setup(0, 9600, 8, uart.PARITY_NONE, uart.STOPBITS_1, 1)
--
uart.setup(0, 9600, 8, uart.PARITY_NONE, uart.STOPBITS_1, 0)

server = nil
data = {}

function connectToAP(ssid, password)
    if password == nil then
        password = ""
    end
    wifi.setmode(wifi.STATION)
    wifi.sta.config(ssid, password, 1)
    return true
end

function getIP()
    if wifi.getmode() == wifi.STATION then
        ip, netmask, gateway = wifi.sta.getip()
        return ip
    else
        ip, netmask, gateway = wifi.ap.getip();
        return ip
    end
end

function getWifiStatus()
    return wifi.sta.status()
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
    return true
end





function getData()
    return data
end

function getDataJSON()
    return cjson.encode(data)
end

function setValue(key, value)
    data[key] = value
    return true
end

function getValue(key, value)
    return data[key]
end

function startServer()
    server = net.createServer(net.TCP)
    server:listen(80, function(conn)
        conn:on("receive", function(socket, payload)
            socket:send("HTTP/1.0 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n" .. getDataJSON())
        end)
        conn:on("sent", function(socket) socket:close() end)
    end)
    return true
end

function stopServer()
    if server ~= nil then
        server:close()
        server = nil;
    end
    return true
end

function restartServer()
    stopServer()
    startServer()
    return true
end
