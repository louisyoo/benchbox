-- add tasks
for _, taskname in ipairs(os.dirs("*"), path.basename) do

    -- add task
    task(taskname)

        -- on run
        on_run(function ()
     
            -- imports
            import("core.base.option")
            import("core.project.task")

            -- get case name
            local casename = option.get("casename")
            assert(casename, "no given testing name, please run `$xmake " .. taskname .. " --help` for getting more info.")

            -- walk all tests
            for _, testname in ipairs(os.dirs(format("%s/%s/%s/*", os.scriptdir(), taskname, casename)), path.basename) do

                -- run the target task
                task.run("run", {target = taskname .. "_" .. casename .. "_" .. testname, arguments = option.get("arguments")})
            end
        end)

        -- set menu
        set_menu({
                        -- usage
                        usage = "xmake " .. taskname .. " casename [options]"

                        -- description
                    ,   description = "The " .. taskname .. " benchmark."

                        -- options
                    ,   options = 
                        {
                            {'n', "casename",   "kv", nil,      "The case name."            
                                                                
                                                                -- show all cases
                                                              , function () 

                                                                    -- imports
                                                                    import("core.project.project")

                                                                    -- make description
                                                                    local description = {}
                                                                    for i, casename in ipairs(os.dirs(format("%s/src/%s/*", project.directory(), taskname)), path.basename) do
                                                                        description[i] = "    - " .. casename
                                                                    end

                                                                    -- get it
                                                                    return description
                                                                end                         }
                        ,   {}
                        ,   {nil, "arguments",  "vs", nil,      "The script arguments."     }
                        }
                    }) 
end

-- add tests
add_subfiles("**/xmake.lua")