# ft_traceroute

A reproduction of the traceroute command.

## Implementation

Basis is pretty simple, send a bunch of UDP packets with an increasing value of TTL to the target (starting from 1, then 2, 3, 4...).
The target will return a TTL exceeded as ICMP packets until we have a TTL high enough to probe it, which will then return a non error packet.

We need a UDP send socket, and an ICMP retreive socket.

## Specifics

### Probes

When sending for exemple 3 probes per hop, you need to increment the dest port each probe, however the TTL stays the same between them, it will only change on the next hop.


## Known limits

The first hop will hit your router, if you send multiple probes/hop, then the first will hit, your router will respond, then the second will hit...
Which leads to our current implementation timing out instead of receiving a TTL exceeded from your router.

