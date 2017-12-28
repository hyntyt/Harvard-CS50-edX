<?php

    // configuration
    require("../includes/config.php"); 
    
    $id = $_SESSION["id"];
    
    $rows = CS50::query("SELECT id, symbol, shares FROM portfolios WHERE user_id = $id");
    
    $positions = [];

    foreach ($rows as $row){
        $stock = lookup($row["symbol"]);
        if ($stock !== false){
            $positions[] = ["name" => $stock["name"], "price" => $stock["price"], "shares" => $row["shares"], "symbol" => $row["symbol"], "total" => sprintf("%.2f", $row["shares"]*$stock["price"])];
        }
    }
    
    $cash = CS50::query("SELECT username, cash FROM users WHERE id=$id");

    // render portfolio
    render("portfolio.php", ["title" => "Welcome", "positions" => $positions, "cash" => $cash]);

?>
