class AddPasswordDigestToAdminUsers < ActiveRecord::Migration[5.0]

  def up
    remove_column "admin_users", "hashed_password"
    add_column "admin_users", "password_digest", :string
  end

  def down
    remove_column "admin_users", "password_digest"
    add_column "admin_users", "hashed_password", :string, :limit => 40
  end

end
