defmodule Contributio.Market.Project do
  use Ecto.Schema
  import Ecto.Changeset

  schema "projects" do
    field :name, :string
    field :repo_id, :integer
    field :description, :string
    field :url, :string
    # field :readme, :string
    field :languages, :map
    # field :owner, :string
    has_one :origin, Contributio.Platforms.Origin
    belongs_to :user, Contributio.Accounts.User
    has_many :tasks, Contributio.Market.Task



#     - Name
# - url
# - description/about
# - readme
# - languages
# - owner/organization
# - tags
# - license?

    timestamps()
  end

  @doc false
  def changeset(project, attrs) do
    project
    |> cast(attrs, [:name, :repo_id, :description, :url, :languages])
    |> validate_required([:name])
  end
end
