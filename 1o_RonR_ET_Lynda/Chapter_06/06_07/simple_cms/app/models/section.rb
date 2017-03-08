class Section < ApplicationRecord

  belongs_to :page
  has_many :section_edits
  
end
