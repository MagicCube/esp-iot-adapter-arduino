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
mode = nil

function connectToAP(ssid, password)
    if password == nil then
        password = ""
    end
    mode = "station"
    wifi.setmode(wifi.STATIONAP)
    wifi.sta.config(ssid, password, 1)
    return true
end

function getIP()
    if mode == "station" then
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
    mode = "ap"
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





function sendFile(socket, filename, contentType)
    if file.open(filename, "r") then
        local header = "HTTP/1.1 "
        header = header .. "200 OK\r\n"
        header = header .. "Content-Type: "
        header = header .. contentType .. "\r\n\r\n"
        socket:send(header, 
            function()
                local function sendChunk()
                    local line = file.read(1024)
                    if line then 
                        socket:send(line, sendChunk) 
                    else
                        file.close()
                        collectgarbage()
                        socket:close()
                    end
                end
                sendChunk()
            end)
    end
end

function processRequest(request, socket)
    if request.path == "/api/data" then
        local header = "HTTP/1.1 "
        header = header .. "200 OK\r\n"
        header = header .. "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n"
        header = header .. "\r\n"
        socket:send(header .. getDataJSON())
        socket:close()
    else
        if request.path == "/" or request.path == "index.html" then
            sendFile(socket, "index.html", "text/html")
        else
            local header = "HTTP/1.1 "
            header = header .. "404 Not Found\r\n"
            header = header .. "Content-Type: text/plain\r\n\r\n"
            socket:send(header .. "Page not found\r\n")
            socket:close()
        end
    end
end





function startServer()
    server = net.createServer(net.TCP)
    server:listen(80, function(conn)
        conn:on("receive", function(socket, payload)
            local _, _, method, path, vars = string.find(payload, "([A-Z]+) (.+)?(.+) HTTP")
            if method == nil then
                _, _, method, path = string.find(payload, "([A-Z]+) (.+) HTTP")
            end
            print(path)
            local request = { path = path };
            processRequest(request, socket);
        end)
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
