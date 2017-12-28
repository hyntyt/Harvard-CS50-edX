<?php
    
    // configuration
    require("../includes/config.php"); 
    
    $id = $_SESSION["id"];
    
    if($_SERVER["REQUEST_METHOD"] == "GET"){
        render("deposit_form.php", ["title" => "Deposit Money"]);
    }
    else if($_SERVER["REQUEST_METHOD"] == "POST"){
        
        $amount = $_POST["amount"];       
        $balancequery = CS50::query("SELECT cash FROM users WHERE id = $id");
        $balance = $balancequery[0]["cash"];
        $newbalance = $balance + $amount;
                
        if($amount != false){
            CS50::query("UPDATE users SET cash = $newbalance WHERE id = $id");
            redirect("/");
        }
        else{
            apologize("Invalid deposit amount.");        
        }
    }
    
?>