//
// Created by Dan on 14/04/2023.
//

#ifndef GAMEENGINESKELETON_SRC_RENDERER_H_
#define GAMEENGINESKELETON_SRC_RENDERER_H_

#include <utility>
#include <iterator>
#include <variant>
#include "Mesh.h"

namespace rts
{

  template <typename RendererImpl>
  class Renderer
  {
	  RendererImpl m_Renderer;
	  rts::Mesh m_ProceduralMesh;
  public:
	  template <typename ...Args>
	  requires (!std::is_same_v<RendererImpl, Renderer>)
	  explicit Renderer(Args&&... args) : m_Renderer(*this, std::forward<Args>(args)...) {}

	  template <std::input_iterator IteratorType>
	  void GenerateMesh(IteratorType begin, IteratorType end)
	  {
		  m_ProceduralMesh.clear();
		  while(begin != end)
		  {
			  std::visit([this](auto &arg) { arg.draw(m_ProceduralMesh.outputBegin());}, (*begin++));
		  }
	  }

	  void draw() noexcept
	  {
		  m_Renderer.draw(m_ProceduralMesh.begin(), m_ProceduralMesh.end());
	  }
  };

} // rts

#endif //GAMEENGINESKELETON_SRC_RENDERER_H_
