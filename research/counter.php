<?php
    
$counterFile = "counter.txt";
$counterBACK = "counter2.txt";
  
Function displayCounter($counterFile, $counterBACK) {
	$fp = fopen($counterFile,"rw");
	$fp2 = fopen($counterBACK, "rw");
	$num = fgets($fp,6);
	$num2 = fgets($fp2,6);
	$num += 1;
	print "<font face='Times New Roman' size='3' color='#CC3300'>"."$num"."</font>";
	if ($num <= 100)
		$num = $num2;
	exec( "rm -rf $counterFile");
	exec( "rm -rf $counterBACK");
	exec( "echo $num > $counterFile");
	exec( "echo $num > $counterBACK");
}
  
if (!file_exists($counterFile)) {
	exec( "echo 0 > $counterFile");
}

if (!file_exists($counterBACK)) {
	exec( "echo 0 > $counterBACK");
}
  
displayCounter($counterFile, $counterBACK);
  
?>
