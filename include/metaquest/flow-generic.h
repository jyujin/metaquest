/**\file
 * \brief Generic game flow
 *
 * Contains a generic game flow object.
 *
 * \copyright
 * This file is part of the Metaquest project, which is released as open source
 * under the terms of an MIT/X11-style licence, described in the COPYING file.
 *
 * \see Documentation: https://ef.gy/documentation/metaquest
 * \see Source Code: https://github.com/jyujin/metaquest
 * \see Licence Terms: https://github.com/jyujin/metaquest/COPYING
 */

#if !defined(METAQUEST_FLOW_GENERIC_H)
#define METAQUEST_FLOW_GENERIC_H

namespace metaquest {
namespace flow {
template <typename interaction, typename logic> class generic {
public:
  generic(void) : interact(), game(interact) {}

  bool run(void) {
    while (true) {
      interact.drawUI(game);

      switch (game.state()) {
      case logic::menu:
        interact.log(game.doMenu());
        break;
      case logic::combat:
        interact.log(game.doCombat());
        break;
      case logic::victory:
        interact.log(game.doVictory());
        break;
      case logic::defeat:
        interact.log(game.doDefeat());
        return true;
      case logic::exit:
        return true;
      default:
        return false;
      }
    }

    return true;
  }

  bool load(efgy::json::json json) {
    game.load(json("game"));
    interact.load(json("interaction"));
    return true;
  }

  efgy::json::json json(void) const {
    efgy::json::json rv;

    rv("game") = game.json();
    rv("interaction") = interact.json();

    return rv;
  }

  interaction interact;
  logic game;
};
}
}

#endif
