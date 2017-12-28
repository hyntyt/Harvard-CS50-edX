<?php 
    
    // configuration
    require("../includes/config.php");
    
    if($_SERVER["REQUEST_METHOD"] == "POST"){ //POST
        
        $input = $_POST["symbol"];
        $amount = $_POST["quantity"];
        $idp = $_SESSION["id"];
        $stock = lookup($_POST["symbol"]);        
        $stocksymbol = $stock["symbol"];
        if($stock != false){
            
            // check balance
            $balancequery = CS50::query("SELECT cash FROM users WHERE id=$idp");
            $balance = $balancequery[0]["cash"]; //works
            
            // Determine cost of transaction
            $buyprice = $stock["price"]; //works
            
            $cost = $buyprice * $amount; //works
            //apologize("Price of this transaction is: $" . $cost);
            
            if($cost > $balance){
                apologize("Insufficient funds for this transaction.");
            }
                
            // add to new/existing
            $newbalance = $balance - $cost;
    
            $stockheld = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? and symbol = ?", $idp, $input);
            
            if(count($stockheld) >= 1){
                //stock is already owned so append the table accordingly
                $oldamount = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? and symbol = ?", $idp, $input);
                $oldamount = $oldamount[0]["shares"];
                $newammount = $oldamount + $amount;
                CS50::query("UPDATE portfolios SET shares = $newammount WHERE user_id = ? and symbol = ?", $idp, $input); //changes all shares, so this is wrong
                CS50::query("UPDATE users SET cash = $newbalance WHERE id = $idp");
                
            }
            else{
                //stock is not already owned so add it to the table
                CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES($idp, '$stocksymbol', $amount)"); //works
                CS50::query("UPDATE users SET cash = $newbalance WHERE id = $idp");
                
            }
            
            // Log transaction accordingly 
            CS50::query("INSERT INTO transactions (id, symbol, status, shares, price, timestamp) VALUES ($idp, '$stocksymbol', 'BUY', $amount, $buyprice, NOW())");
                
            render("buy_summary.php", ["title" => "Stock Sale Summary", "stock" => $stock, "amount" => $amount, "cost" => $cost, "newbalance" => $newbalance]); //success
        }
        else{
            apologize("Invalid stock code.");        
        }
        
    } 
    else{ //GET
        //$idg = $_SESSION["id"];
        render("buy_form.php", ["title" => "Buy Stocks"]); 
    }
    
?>