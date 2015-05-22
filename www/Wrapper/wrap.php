<?php

$parts=explode("?",$argv[1],2);

$params=explode("&",$parts[1]);

$postParams=explode("&",$argv[2]);
foreach ($params as $param)
{
	$p=explode("=",$param);
	$_GET[$p[0]]=$p[1];
}

foreach ($postParams as $param)
{
	$p=explode("=",$param);
	$_POST[$p[0]]=$p[1] ;
}

include($parts[0]);


?>
