import click
import json
import mplfinance as mpf
import pandas as pd
import numpy as np


def load_data(file):
    with open(file, "r") as f:
        data = json.load(f)
    return data


def orders_plot(candles, orders):
    orders_np = np.full(len(candles), np.nan)

    for order in orders:
        order_time = pd.to_datetime(order["time"], unit="s")
        if order_time in candles.index:
            idx = candles.index.get_loc(order_time)
            orders_np[idx] = order["price"]

    buy = len(orders) and order["type"] == "BUY"

    return mpf.make_addplot(
        orders_np,
        type='scatter',
        marker='^' if buy else 'v',
        color='green' if buy else 'red',
        markersize=50,
        secondary_y=False,
        y_on_right=False
    )

def balance_plot(candles, balances):
    balance_np = np.full(len(candles), np.nan)

    for balance in balances:
        balance_time = pd.to_datetime(balance["time"], unit="s")
        if balance_time in candles.index:
            idx = candles.index.get_loc(balance_time)
            balance_np[idx] = balance["balance"]

    return mpf.make_addplot(
        balance_np,
        type='line',
        color='blue',
        secondary_y=False,
        panel=2,
        ylabel='Balance',
        y_on_right=False
    )

@click.command()
@click.argument("inp", type=click.Path(exists=True))
@click.argument("out", type=click.Path())
@click.argument("size", type=click.INT, default=1000000)
def plot(inp, out, size):
    data = load_data(inp)

    candles = pd.DataFrame(data["candles"][-min(size, len(data["candles"])):])
    candles.index = pd.to_datetime(candles["time"], unit='s')

    mpf.plot(
        candles,
        addplot=[
            orders_plot(candles, data["orders"]["buy"]),
            orders_plot(candles, data["orders"]["sell"]),
            balance_plot(candles, data["balances"]),
        ],
        type='candle',
        volume=True,
        savefig=out,
        fontscale=1.0,
        style='yahoo',
        tight_layout=True,
    )


if __name__ == "__main__":
    plot()
