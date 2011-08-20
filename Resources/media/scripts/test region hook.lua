-- first we tell lua about our c# program
luanet.load_assembly("Lymph")

-- then we do stuff!

-- this only gets run if we explicitly call it!
function triggerTestFunction(s1, s2, tf)
	if isEnterFlag(tf) then
		print("enter" .. getBodyName(s2))
	else
		print("leave" .. getBodyName(s2))
	end
end

-- this runs when the file is run, which is usually right at the beginning of the level!
-- remember that this can only reference functions that already exist at the time of running, so it's best to make sure you only reference other lua functions in the same file since there's no set order that the scripts are loaded in.
hookFunctionToTriggerRegion("test trigger area", triggerTestFunction)