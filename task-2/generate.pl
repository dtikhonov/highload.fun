#!/usr/bin/perl

$count = shift;

@chars = ('0'..'9', 'A'..'F', 'a'..'f');

for ($i = 0; $i < $count; ++$i) {
    $len = 1 + int(rand(15));
    $str = '';
    for ($j = 0; $j < $len; ++$j) {
        $str .= $chars[ rand @chars ];
    }
    print $str, "\n";
}
