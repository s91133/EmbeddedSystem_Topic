<?php
$cmd = "curl -F '__VIEWSTATE=/wEPDwUJOTY0MjAwMjYyD2QWAgIDDxYCHgdlbmN0eXBlBRNtdWx0aXBhcnQvZm9ybS1kYXRhFgICBQ8PFgIeBFRleHQFFeS9v+eUqOasoeaVuO+8mjAwNTgwNGRkZFy5+PZvhDOODwK0wNVho5G2hWShBfID3IaQFixykJMs' -F 'Button1=上傳' -F '__EVENTARGUMENT=' -F '__EVENTTARGET=' -F 'FileUpload1=@".$argv[1]."' -F '__EVENTVALIDATION=/wEdAAKVrc7MAn4FbBxWlSB/37nyzfg78Z8BXhXifTCAVkevd8Yd8Rp0/W2egGJREVSWyXmSeA9A6y73wX/eorketyAq' -F '__VIEWSTATEGENERATOR=E550B164' http://www.ezonesoft.com.tw/weblpr/ 2>/dev/null";
$output = shell_exec($cmd);
$output = explode("__", explode("車牌：", $output)[1])[0];
//echo $output;
//print_r($argv);
file_put_contents(dirname(__FILE__).'/vehicle.txt', $output);
echo dirname(__FILE__).'vehicle.txt';
?>
