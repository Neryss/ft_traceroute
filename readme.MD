# ft_traceroute

A reproduction of the traceroute command.

## How to use

You can run the start script, you must be root (since we use RAW sockets):

`sudo ./start.sh`

This will start the VM, you can then compile the project using `make`.

After that, run the program using `./ft_traceroute [options] <host>`

Note: you can compile this outside of the vm if you want to test it real quick.

## Implementation

Basis is pretty simple, send a bunch of UDP packets with an increasing value of TTL to the target (starting from 1, then 2, 3, 4...).
Routers on the way to the target will return a TTL exceeded in their ICMP packets. This will continue until we reach a TTL value high enough to reach our target, which will then stop replying with TTL exceeded packets.
Each probe sent gets an associated RTT and gets printed.

## Specifics

### Probes

When sending for exemple 3 probes per hop, you need to increment the dest port each probe, however the TTL stays the same between them, it will only change on the next hop.


## Known limits

We face an issue where the second hop fails each time when routing to google.com for exemple, if we send 3 probes, each will fail after a set timeout, which corresponds to the current lib implementation as shown here:

'If there is no response within a 5 sec. timeout interval (changed with the -w flag), a "*" is printed for that probe.'

(source: https://github.com/openbsd/src/blob/master/usr.sbin/traceroute/traceroute.c#L79)

HOWEVER, the official traceroute times out way faster than the predicted 15s (3probes * 5s), no idea why ?
