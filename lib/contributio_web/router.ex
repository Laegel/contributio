defmodule ContributioWeb.Router do
  use ContributioWeb, :router

  require Logger

  pipeline :browser do
    plug :accepts, ["html"]
    plug :fetch_session
    plug :fetch_flash
    plug :protect_from_forgery
    plug :put_secure_browser_headers
  end

  pipeline :api do
    plug :accepts, ["json"]
    plug ContributioWeb.Context
  end

  scope "/", ContributioWeb do
    post "/webhooks", WebhooksController, :dispatch
  end

  scope "/" do
    pipe_through :api

    forward "/graph", Absinthe.Plug,
      schema: Contributio.Schema,
      before_send: {__MODULE__, :before_send}

    forward "/graphiql", Absinthe.Plug.GraphiQL, schema: Contributio.Schema
  end

  def before_send(conn, %Absinthe.Blueprint{execution: %{context: %{token: token}}}) do
    max_age = 2592000
    conn
    |> put_resp_cookie("ctiotoken", token, http_only: true, max_age: max_age)
    |> put_resp_cookie(
      "ctiotokenexpire",
      Timex.now() |> Timex.shift(seconds: max_age) |> Timex.format!("%FT%T.%f%z", :strftime),
      http_only: false, max_age: max_age
    )
  end

  def before_send(conn, _), do: conn

  # Enables LiveDashboard only for development
  #
  # If you want to use the LiveDashboard in production, you should put
  # it behind authentication and allow only admins to access it.
  # If your application does not have an admins-only section yet,
  # you can use Plug.BasicAuth to set up some basic authentication
  # as long as you are also using SSL (which you should anyway).
  if Mix.env() in [:dev, :test] do
    import Phoenix.LiveDashboard.Router

    scope "/" do
      pipe_through :browser
      live_dashboard "/dashboard", metrics: ContributioWeb.Telemetry
    end
  end

  scope "/", ContributioWeb do
    # Use the default browser stack
    pipe_through :browser

    get "/*path", PageController, :index
  end
end
