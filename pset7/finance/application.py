from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    user_id = session['user_id']
    #get total cash
    cash = get_cash(user_id);
    #get user's shares
    user_shares = parse_transactions(get_transactions(user_id))
    
    total = 0
    for entry in user_shares:
        total += entry['total']
    total = total+cash
    
    return render_template('index.html', cash=cash, total=total, entries=user_shares)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == 'POST':

        user_id = session["user_id"]
    
        # ensure symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology('must provide symbol')

        # ensure correct number of shares was submitted    
        shares = checkShares(request.form.get("shares"))
        
        if not shares > 0:
            return apology('invalid input')
            
        # ensure submitted symbol is correct
        if not checkSymbol(symbol):
            return apology('invalid symbol')
        price, name, symbol = checkSymbol(symbol)
    
        # get available cash and check for solvency
        cash = get_cash(user_id)
        transaction_result = cash - price * shares
        if transaction_result < 0:
            return apology("can't afford")

        # add transaction
        db.execute('INSERT INTO transactions (shares, price, symbol, name, user_id) VALUES (:shares, :price, :symbol, :name, :user_id)',shares=shares, price=price, user_id=user_id, symbol=symbol, name=name)
        
        # update cash
        db.execute("UPDATE users SET cash=:cash WHERE id=:user_id", cash=transaction_result, user_id=user_id)

        flash('Bought!')
        return redirect(url_for("index"))
    
    else:
        return render_template('buy.html')

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    transactions = db.execute('SELECT symbol, shares, price, timestamp FROM transactions WHERE user_id = :user_id', user_id=session["user_id"])

    return render_template('history.html', entries=transactions)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("share"):
            return apology("must provide share")
        share = lookup(request.form.get("share"))
        
        return render_template("quoted.html", share = share )

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")
    

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")
        # ensure repassword was submitted    
        elif not request.form.get("repassword"):
            return apology("must provide password")
        # ensure password and repassword is match    
        elif not request.form.get("password") == request.form.get("repassword"):
            return apology("Password's not match")
            
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        if len(rows) > 0:
            return apology("user alredy exist")
        
        # encrypt passsword
        hash = pwd_context.encrypt(request.form.get("password"))
        
        # query database for add user
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get("username"), hash=hash)


        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == 'POST':
        
        user_id = session["user_id"]
        
        # ensure symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology('need a symbol')
            
        
        # ensure correct number of shares was submitted    
        shares = checkShares(request.form.get("shares"))
        
        if not shares > 0:
            return apology('invalid input')
        
        # ensure submitted symbol is correct
        if not checkSymbol(symbol):
            return apology('invalid symbol')   
        price, name, symbol = checkSymbol(symbol)
        

        shares_available = db.execute("SELECT SUM(shares) FROM transactions WHERE user_id=:user_id AND symbol=:smb" , user_id=user_id, smb=symbol)[0]['SUM(shares)']
        if shares_available - shares < 0:
            return apology('too many shares')
            
        cash = get_cash(user_id)
        transaction_result = cash + shares * price
        
        # add transaction
        db.execute('INSERT INTO transactions (shares, price, symbol, name, user_id) VALUES (:shares, :price, :symbol, :name, :user_id)', shares=-shares, price=price, user_id=user_id, symbol=symbol, name=name)
        
        db.execute("UPDATE users SET cash=:cash WHERE id=:user_id", cash=transaction_result, user_id=user_id)

        flash('SOLD!')
        return redirect(url_for("index"))
    else:
        return render_template('sell.html')
        

@app.route("/changepass", methods=["GET", "POST"])
@login_required
def changepass():
    if request.method == 'POST':
        
        user_id = session['user_id']
        current_pass = request.form.get("current")
        new = request.form.get("new")
        new_d = request.form.get("new_d")
       
        # ensure current password was submitted
        if not current_pass:
            return apology("must provide current password")

        # ensure new password was submitted
        if not new:
            return apology("must provide new password")
            
        # ensure new password and copy match
        if new != new_d:
            return apology("passwords don't match")

        # get current password hash
        rows = db.execute("SELECT hash FROM users WHERE id=:user_id", user_id=user_id)

        # ensure password is correct
        if not pwd_context.verify(current_pass, rows[0]["hash"]):
            return apology("invalid password")
        
        # update password
        passhash = pwd_context.encrypt(new)
        db.execute("UPDATE users SET hash=:passhash WHERE id=:user_id", user_id=user_id, passhash=passhash)
        
        flash('Your password has been changed!')
        return redirect(url_for("index"))
    
    else:
        return render_template('changepass.html')
