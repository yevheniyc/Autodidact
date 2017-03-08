class Page < ApplicationRecord

  belongs_to :subject, { :optional => false }
  has_many :sections

end
