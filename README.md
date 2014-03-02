convio_signup
=============

This drupal module allows admins to create simple email list signup forms.

The signup forms create constituent records in the Convio Luminate Online database via Convio's createOrUpdate API method (http://open.convio.com/api/#constituent_api.createOrUpdate_method.html). To use this module, the Convio API module, which sends and processes Convio API requests, must be installed and configured.

Once the convio_api and convio_signup modules are installed and configured, an admin can create new signup blocks by visiting Administration > Structure > Convio Signup Forms Configuration > Create Convio Signup Form. After filling out and submitting the form on this page, a new block containing the email signup form is available for admins to place on the site (Administration > Structure > Blocks).

To add more blocks and edit or delete existing blocks, admins can visit Administration > Structure > Convio Signup Forms Configuration.

Resources
=========
convio_api module: https://github.com/milodesc/convio_api
Convio API createOrUpdate documentation: http://open.convio.com/api/#constituent_api.createOrUpdate_method.html
Convio API general documentation: http://open.convio.com/api/#main

