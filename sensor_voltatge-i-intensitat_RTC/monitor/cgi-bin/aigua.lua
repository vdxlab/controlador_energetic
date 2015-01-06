#!/usr/bin/lua

json = require("luci.json")
dbdir = "/root/db"
fields = {"dalt_dist", "verd_dist"}

function string:split( inSplitPattern, outResults )
  if not outResults then
    outResults = { }
  end
  local theStart = 1
  local theSplitStart, theSplitEnd = string.find( self, inSplitPattern, theStart )
  while theSplitStart do
    table.insert( outResults, string.sub( self, theStart, theSplitStart-1 ) )
    theStart = theSplitEnd + 1
    theSplitStart, theSplitEnd = string.find( self, inSplitPattern, theStart )
  end
  table.insert( outResults, string.sub( self, theStart ) )
  return outResults
end

function get_time()
    return os.date("%Y%m%d%H%M")
end

function read_serial()
	local output = {}
	local log = "/tmp/serial.log"
	local f = io.open(log,"r")
	local len = f:seek("end")
	f:seek("set", len - 1024)
	local text = f:read("*a")
	f:close()
	lines = text:split('\n')
	output.dalt_dist = 0
	output.verd_dist = 0
	output.bomba_aljub = 'off'
	output.bomba_altura = 'off'
    output.start = false
	for _,l in ipairs(lines) do
		local line = l:split(":")
		if #line > 1 then 
			line[1] = line[1]:gsub('%s','')
			line[1] = line[1]:gsub('%d','')
			line[2] = line[2]:gsub('%s','')
			if line[1] == "distancia_dalt" then
				output.dalt_dist = line[2]
			elseif line[1] == "distancia_verd" then
				output.verd_dist = line[2]
			elseif line[1] == "bomba_aljub" then
				output.bomba_aljub = line[2]
			elseif line[1] == "bomba_altura" then
				output.bomba_altura = line[2]
            elseif line[1] == "info" then
                if line[2] == "start" then
                    output.start = true
                end
			end
		end
	end
	return output
end

-- [ {"date":X1, value:"Y1"}, {"date":X2, value:"Y2"} ]
function check_start(data)
    local save = false
    local jdata = nil
    local f = io.open(dbdir..'/start','r')
    if f ~= nil then
        jdata = json.decode(f:read('*a'))
        f:close()
    end
    -- save only changes
    if jdata ~= nil then
        if data["start"] and not jdata[#jdata].value then
            jdata[#jdata+1] = { date = get_time(), value = true}
            save = true
        elseif not data["start"] and jdata[#jdata].value then
            jdata[#jdata+1] = { date = get_time(), value = false}
            save = true
        end
    end
    if jdata == nil or f == nil then
        if jdata == nil then
            jdata = {{date = get_time(), value = data.start}}
        end
        save = true
    end
    if save then
        f = io.open(dbdir..'/start','w')
        f:write(json.encode(jdata))
        print(json.encode(jdata))
        f:close()
    end
end

function save_distances(data)
    local f
    local output = {}
    local time = get_time()
    for _,l in ipairs(fields) do
        local f = io.open(dbdir..'/'..l,'r')
        local jdata = nil
        if f ~= nil then
            jdata = json.decode(f:read('*a'))
            f:close()
        end
        f = io.open(dbdir..'/'..l,'w')
        --for i,k in pairs(jdata[1]) do print(i) end
        if f == nil or jdata == nil then
            f:write(json.encode({{date = get_time(), value = data[l]}}))
        else
            jdata[#jdata+1] = {date = get_time(), value = data[l]}
            f:write(json.encode(jdata))
            print(json.encode(jdata))
        end
        --print(data[l])
        f:close()
    end
end

---------
-- MAIN --
----------
info = os.getenv ("QUERY_STRING")
print ("Content-type: application/json\n")
serial = read_serial()

if info == "distances_update" then
    save_distances(serial)
elseif info == "start_update" then
    check_start(serial)
elseif info:find("stats=") ~= nil then
    fname = info:split('=')[2]
    f = io.open(dbdir..'/'..fname,'r')
    if f ~= nil then
        print(f:read('*a'))
       f:close()
    end
else
    print(json.encode(serial))
    
end   
