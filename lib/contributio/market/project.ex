defmodule Contributio.Market.Project do
  use Ecto.Schema
  import Ecto.Changeset

  schema "projects" do
    field :name, :string
    field :repo_id, :string
    field :description, :string
    field :url, :string
    field :languages, :map
    field :topics, {:array, :string}
    # field :readme, :string
    field :license, :string
    field :status, :integer
    # belongs_to :origin, Contributio.Platforms.Origin
    belongs_to :user, Contributio.Accounts.User
    has_many :tasks, Contributio.Market.Task
  end

  @doc false
  def changeset(project, attrs) do
    project
    |> cast(attrs, [
      :name,
      :repo_id,
      :description,
      :url,
      :languages,
      :user_id,
      :topics,
      :license,
      :status
    ])
    # |> validate_required([:name])
  end
end
