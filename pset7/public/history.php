<?php

    // configuration
    require("../includes/config.php"); 
    
    $hid = $_SESSION["id"];
    
    $rows = CS50::query("SELECT id, symbol, status, shares, price, timestamp FROM transactions WHERE id = $hid");

    $positions = [];

    foreach ($rows as $row){
        if ($hid !== false){
            $positions[] = ["symbol" => $row["symbol"], "status" => $row["status"], "shares" => $row["shares"], "symbol" => $row["symbol"], "price" => $row["price"], "timestamp" => $row["timestamp"]];
        }  
    }
    
    $cash = CS50::query("SELECT username, cash FROM users WHERE id=$hid");

    // render portfolio
    render("history_display.php", ["title" => "Transaction History", "positions" => $positions, "cash" => $cash]);

?>
