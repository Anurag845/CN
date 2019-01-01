set ns [new Simulator]

$ns color 1 Blue
$ns color 2 Red

set nf [open a.nam w]
$ns namtrace-all $nf

proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam a.nam &
	exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

$ns duplex-link $n3 $n1 2Mb 10ms DropTail
$ns duplex-link $n2 $n4 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n0 $n1 2Mb 10ms DropTail
$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns queue-limit $n1 $n2 10

$ns duplex-link-op $n3 $n1 orient right-up
$ns duplex-link-op $n1 $n2 orient right
$ns duplex-link-op $n2 $n4 orient right-down
$ns duplex-link-op $n2 $n0 orient left-up
$ns duplex-link-op $n1 $n0 orient right-up

$ns duplex-link-op $n1 $n2 queuePos 1.0

set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n3 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n4 $sink
$ns connect $tcp $sink
$tcp set fid_ 1

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP
$ftp set packet_size_ 1000

set udp [new Agent/UDP]
$ns attach-agent $n3 $udp
set null [new Agent/Null]
$ns attach-agent $n0 $null
$ns connect $udp $null
$udp set fid_ 2

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set random_ false
$cbr set rate_ 1mb
$cbr set packet_size_ 1000

$ns at 1.0 "$ftp start"
$ns at 1.5 "$cbr start"
$ns at 2.0 "$ftp stop"
$ns at 2.5 "$cbr stop"
$ns at 3.0 "finish"

$ns run
