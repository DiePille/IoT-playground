servo1 = 3
gpio.mode(servo1, gpio.OUTPUT)


if srv~=nil then
  srv:close()

else
    srv = net.createServer(net.TCP)
end

-- listen 2 your <3
srv:listen(80,function(connection)
    connection:on("receive", function(client,request)
        local buf = "";
        local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP");
        if(method == nil)then
            _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP");
        end
        local _GET = {}
        if (vars ~= nil)then
            for k, v in string.gmatch(vars, "(%w+)=(%w+)&*") do
                _GET[k] = v
            end
        end
        buf = buf.."<h1>Iot Testpage</h1>";
        buf = buf.."<p>Servo(GPIO1) <a href=\"?pin=ON1\"><button>ON</button></a>&nbsp;<a href=\"?pin=OFF1\"><button>OFF</button></a></p>";
        local _on,_off = "",""
        if(_GET.pin == "ON1")then
              gpio.write(servo1, gpio.HIGH);
        elseif(_GET.pin == "OFF1")then
              gpio.write(servo1, gpio.LOW);
        end
        client:send(buf);
        client:close();
        collectgarbage();
    end)
end)
