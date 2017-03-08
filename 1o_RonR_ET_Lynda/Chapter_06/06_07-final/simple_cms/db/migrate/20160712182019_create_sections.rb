class CreateSections < ActiveRecord::Migration[5.0]

  def up
    create_table :sections do |t|
      t.integer "page_id"
      t.string "name"
      t.integer "position"
      t.boolean "visible", :default => false
      t.string "content_type"
      t.text "content"
      t.timestamps
    end
    add_index("sections", "page_id")
  end

  def down
    # don't need to drop indexes when dropping the whole table
    drop_table :sections
  end

end
