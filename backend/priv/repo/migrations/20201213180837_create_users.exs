defmodule Contributio.Repo.Migrations.CreateUsers do
  use Ecto.Migration

  def change do
    create table(:users) do
      add :email, :string
      add :hash, :string
      add :token, :string

      timestamps()
    end

  end
end
