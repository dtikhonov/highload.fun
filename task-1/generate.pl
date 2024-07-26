#!/usr/bin/perl

$count = shift;
$max = shift // (1 << 31);

while ($count-- > 0) {
    print int(rand($max)), "\n";
}
