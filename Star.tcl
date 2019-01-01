set ns [new Simulator]

$ns color 1 Blue
$ns color 2 Red

set nf [open out.nam w]
$ns namtrace-all $nf
set nf1 [open out.tr w]
$ns trace-all $nf1

proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam out.nam &
	exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

$ns duplex-link $n0 $n4 2Mb 10ms DropTail
$ns duplex-link $n4 $n1 1.5Mb 10ms DropTail

$ns duplex-link $n2 $n4 2Mb 10ms DropTail
$ns duplex-link $n4 $n3 1.5Mb 10ms DropTail

$ns queue-limit $n4 $n1 10
$ns queue-limit $n4 $n3 10

$ns duplex-link-op $n0 $n4 orient down
$ns duplex-link-op $n4 $n1 orient right
$ns duplex-link-op $n4 $n2 orient down
$ns duplex-link-op $n4 $n3 orient left

$ns duplex-link-op $n4 $n1 queuePos 0.8
$ns duplex-link-op $n4 $n3 queuePos 0.8

set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n1 $sink
$ns connect $tcp $sink
$tcp set fid_ 1

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

set udp [new Agent/UDP]
$ns attach-agent $n2 $udp
set null [new Agent/Null]
$ns attach-agent $n3 $null
$ns connect $udp $null
$udp set fid_ 2

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set random_ false
$cbr set rate_ 1mb
$cbr set packet_size_ 1000

$ns at 1.0 "$ftp start"
$ns at 2.0 "$cbr start"
$ns at 3.0 "$ftp stop"
$ns at 4.0 "$cbr stop"
$ns at 5.0 "finish"

$ns run
