log = "/tmp/serial.log"

function sleep(n)
  os.execute("sleep " .. tonumber(n))
end

function file_exists(name)
   local f = io.open(name,"r")
   if f ~= nil then io.close(f) return true else return false end
end


function open_serial()
        dev = nil
        local i
        dev = "/dev/ttyS0"
        if dev == nil then
                serialin = nil
                file = nil
                print("Cannot find serial device")
        else
                print("Using device " .. dev)
                os.execute("stty -F "..dev.." 9600" .. " &")
                sleep(2)
                file = io.open(log,"a")
                serialin = io.open(dev,"r") or nil
        end
        itc = 0
end

open_serial()

while 1 do
    if serialin ~= nil then
        input = serialin:read("*l")
        if input ~= nil and #input > 5 then
            print(os.time()..": "..input)
            file:write(input .. "\n")
        end
        itc = itc + 1
        if itc > 9 then
            file:close()
            file = io.open(log,"a")
            itc = 0
        end
    else
        print("Cannot open serial port")
        sleep(1)
        open_serial()
    end
end

serialin:close()
file:close()


