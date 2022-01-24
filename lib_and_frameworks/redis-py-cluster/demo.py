# -*- coding: utf-8 -*-


from rediscluster import RedisCluster

startup_nodes = [
        {'host':'localhost','port':'30001'},
        {'host':'localhost','port':'30002'}, 
        {'host':'localhost','port':'30003'}, 
        {'host':'localhost','port':'30004'},
        {'host':'localhost','port':'30005'},
        {'host':'localhost','port':'30006'}

]


if __name__ == "__main__":
    rc = RedisCluster(startup_nodes=startup_nodes, decode_responses=True)
    rc.set("foo", "bar0")
    print(rc.get("foo"))
    rc.set("foo", "bar1") 
    print(rc.get("foo")) 
    rc.delete("foo")
    a = rc.delete("iuyaiusuidyaids") # This should be error since delete an nonexists key.
    print(a)
