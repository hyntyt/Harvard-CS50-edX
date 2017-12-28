<div>

    <div id="greeting">
        <?php
            print("User: " . $cash[0]["username"]);
            print("  -    Balance: $" . sprintf("%.2f",$cash[0]["cash"]));
        ?>
    </div>

    <table id="overview">
        <?php

            print("<tr>");
            print("<th>Symbol</th>");
            print("<th>Name</th>");
            print("<th>Shares</th>");
            print("<th>Price</th>");
            print("<th>Total</th>");
            print("</tr>");
        
            foreach ($positions as $position){
                print("<tr>");
                print("<td>" . $position["symbol"] . " </td>");
                print("<td>" . $position["name"] . " </td>");
                print("<td>" . $position["shares"] . " </td>");
                print("<td>" . "$" . $position["price"] . " </td>");
                print("<td>" . "$" . $position["total"] . " </td>");
                print("</tr>");
        }

    ?>
    </table>

</div>
