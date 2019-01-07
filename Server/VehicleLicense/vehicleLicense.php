<?php
$cmd = "curl -F '__VIEWSTATE=/wEPDwUJOTY0MjAwMjYyD2QWAgIDDxYCHgdlbmN0eXBlBRNtdWx0aXBhcnQvZm9ybS1kYXRhFgICBQ8PFgIeBFRleHQFFeS9v+eUqOasoeaVuO+8mjAwNTgwNGRkZFy5+PZvhDOODwK0wNVho5G2hWShBfID3IaQFixykJMs' -F 'Button1=上傳' -F '__EVENTARGUMENT=' -F '__EVENTTARGET=' -F 'FileUpload1=@".$argv[1]."' -F '__EVENTVALIDATION=/wEdAAKVrc7MAn4FbBxWlSB/37nyzfg78Z8BXhXifTCAVkevd8Yd8Rp0/W2egGJREVSWyXmSeA9A6y73wX/eorketyAq' -F '__VIEWSTATEGENERATOR=E550B164' http://www.ezonesoft.com.tw/weblpr/ 2>/dev/null";
$output = shell_exec($cmd);
$json = array();
//file_put_contents('./rawDate.txt', $output);
//echo (explode("辨識", explode("：", $output)[1])[0]);
if(strcmp(explode("辨識", explode("：", explode("車牌", $output)[7])[1])[0], "無法")){
//	echo "True";
	$output = explode("__", explode("：", explode("車牌", $output)[7])[1])[0];
	$json['isVehicle'] = true;
	$json['Vehicle'] = $output;
}else{
//	echo "False";
	$json['isVehicle'] = false;
	$json['Vehicle'] = $output;
}
$output = json_encode($json);
//echo $output;
//print_r($argv);
file_put_contents(dirname(__FILE__).'/vehicle.txt', $output);
//echo dirname(__FILE__).'/vehicle.txt';
?>
